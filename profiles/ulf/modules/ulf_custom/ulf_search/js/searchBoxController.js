/**
 * @file
 * This is the main controller for the application.
 *
 * It controls the search box and filters.
 */

/**
 * Overrides the default searchBoxApp controller.
 */
angular.module('searchBoxApp').controller('UlfBoxController', ['CONFIG', 'communicatorService', 'searchProxyService', '$scope', '$location', '$rootScope', '$window',
  function (CONFIG, communicatorService, searchProxyService, $scope, $location, $rootScope, $window) {
    'use strict';

    /**
     * Listen to location change event to handle (back/forward button).
     */
    $rootScope.$on('$locationChangeSuccess', function(newLocation, oldLocation) {
      $rootScope.actualHash = $location.hash();
    });

    /**
     *
     */
    $rootScope.$watch(function () {
      return $location.hash();
    }, function (newHash, oldHash) {
      if($rootScope.actualHash === newHash) {
        // @TODO: Figure out why promises stop working when the back/forward
        // buttons in the browser have been user.
        $window.location.reload();
      }
    });

    $scope.greaterThan = function(prop, val){
      return function(item){
        return item[prop] > val;
      }
    };

    /**
     * Find the currently select filters/facets.
     *
     * @param filters
     *   The selected filters return from search.
     *
     * @returns {{}}
     *   The filter with correct names indexed by field name.
     */
    function getSelectedFilters(filters) {
      if (filters.hasOwnProperty('taxonomy')) {
        var taxonomies = filters.taxonomy;
        var selectedFilters = {};
        for (var field in taxonomies) {
          selectedFilters[field] = [];
          for (var key in taxonomies[field]) {
            if (taxonomies[field][key]) {
              selectedFilters[field].push(key);
            }
          }
        }
      }

      return selectedFilters;
    }

    /**
     * Execute the search and emit the results.
     */
    function search() {
      // Send info to results that a new search have started.
      communicatorService.$emit('searching', {});

      // Add sorting to the search query.
      if (CONFIG.provider.hasOwnProperty('sorting')) {
        $scope.query.sort = {};
        $scope.query.sort[CONFIG.provider.sorting.field] = CONFIG.provider.sorting.order;
      }

      // Start the search request.
      searchProxyService.search($scope.query).then(
        function (data) {
          // Updated filters.
          searchProxyService.getFilters().then(
            function (filters) {
              $scope.filters = filters;
            },
            function (reason) {
              console.error(reason);
            }
          );

          // Updated selected filters base on search query.
          if ($scope.query.hasOwnProperty('filters')) {
            var filters = angular.copy($scope.query.filters);
            $scope.selectedFilters = getSelectedFilters(filters);
          }

          // Send results.
          var res = {
            "hits": data
          };

          // Add pager info to the results.
          if (CONFIG.provider.hasOwnProperty('pager')) {
            res.pager = $scope.query.pager
          }

          communicatorService.$emit('hits', res);
        },
        function (reason) {
          console.error(reason);
        }
      );

      // Update map search results.
      mapSearch();
    }

    /**
     * Search for results to be displayed on maps.
     *
     * Mainly used because maps don't need data limited by pager.
     */
    function mapSearch() {
      if (CONFIG.provider.hasOwnProperty('map')) {
        var query = angular.copy($scope.query);
        if (CONFIG.provider.hasOwnProperty('pager')) {
          query.pager.size = CONFIG.provider.map.points;
          query.pager.page = 0;
        }
        searchProxyService.search(query, true).then(
          function (data) {
            // Send results.
            communicatorService.$emit('mapSearchHits', data);
          },
          function (reason) {
            console.error(reason);
          }
        );
      }
    }

    // Resetting the pager
    function resetPager() {
      if (CONFIG.provider.hasOwnProperty('pager') || CONFIG.query.hasOwnProperty('pager')) {
        $scope.query.pager = angular.copy(CONFIG.provider.pager);
      }
    }

    /**
     * Init the controller.
     */
    function init() {
      // Get state from previous searches.
      var state = searchProxyService.getState();

      // Get filters.
      $scope.filters = state.filters;

      // Set template to use.
      var box_template = CONFIG.templates.box;
      if (box_template.charAt(0) === "/") {
        $scope.template = box_template;
      }
      else {
        $scope.template = "/" + box_template;
      }

      // Init the query object.
      $scope.query = {
        'text': '',
        'filters': {}
      };

      // Init selected filters.
      $scope.selectedFilters = {};

      // Check if any intervals have been configured.
      if (CONFIG.provider.hasOwnProperty('intervals')) {
        $scope.intervals = CONFIG.provider.intervals;
        $scope.query.intervals = {};
      }

      // Check if any dates have been configured.
      if (CONFIG.provider.hasOwnProperty('dates')) {
        $scope.dates = CONFIG.provider.dates;
        $scope.query.dates = {};
      }

      // Check if any search query have been located from the hash tag.
      if (state.hasOwnProperty('query')) {
        // Query found in state, so execute that search.
        $scope.query = state.query;
        search();
      }
      else {
        // Check if the provider supports an pager.
        resetPager();

        // Check if an initial search should be executed.
        if (CONFIG.hasOwnProperty('initialQueryText')) {
          $scope.query.text = angular.copy(CONFIG.initialQueryText);

          // Execute the search.
          search();
        }
        else {
          // Get filters based on search content (maybe slow).
          searchProxyService.getFilters().then(
            function (filters) {
              $scope.filters = filters;
            },
            function (reason) {
              console.error(reason);
            }
          );
        }
      }

      // Set selected filters class array.
      $scope.toggleFilterClasses = {};
    }

    /**
     * Handle pager updated from the search result application.
     */
    communicatorService.$on('pager', function (event, data) {
      $scope.query.pager = {
        'size': data.size,
        'page': data.page
      };
      search();
    });

    /**
     * Handle pager updated from the search result application.
     */
    communicatorService.$on('requestMapSearch', function (event, data) {
      mapSearch();
    });

    /**
     * Click handel for searches.
     */
    $scope.searchClicked = function searchClicked() {
      resetPager();
      search();
    };

    /**
     * Open clicked filter.
     *
     * @param id
     *   The ID of the filter to open.
     */
    $scope.openFilter = function openFilter(id) {
      if ($scope.toggleFilterClasses.hasOwnProperty(id)) {
        // Same filter clicked just, close it.
        $scope.toggleFilterClasses = {
          'active': false
        };

      }
      else {
        // Close active filter.
        if ($scope.toggleFilterClasses.active) {
          $scope.toggleFilterClasses = {
            'active': false
          };
        }

        // Open new filter.
        $scope.toggleFilterClasses['active'] = true;
        $scope.toggleFilterClasses[id] = ['is-active', 'is-visible'];
      }
    };

    /**
     * Remove filter from the current query.
     *
     * @param field
     *   The field/filter to remove the filter from.
     * @param filter
     *   The filter word its self.
     */
    $scope.removeFilter = function removeFilter(field, filter) {
      if ($scope.query.filters.taxonomy[field].hasOwnProperty(filter)) {
        // Remove the filter for current query.
        delete $scope.query.filters.taxonomy[field][filter];

        // Update search.
        resetPager();
        search();
      }
    };

    /**
     * Resets the current search to default.
     */
    $scope.reset = function reset() {
      // Reset filters
      $scope.query.filters = {};
      $scope.selectedFilters = {};

      // Reset intervals.
      if (CONFIG.provider.hasOwnProperty('intervals')) {
        $scope.query.intervals = {};
      }

      if (CONFIG.provider.hasOwnProperty('dates')) {
        $scope.query.dates = {};
      }

      // Reset pager.
      resetPager();

      // Check if initail query exists.
      if (CONFIG.hasOwnProperty('initialQueryText')) {
        $scope.query.text = angular.copy(CONFIG.initialQueryText);

        search();
      }
      else {
        // No initial query.
        $scope.query.query = '';

        // Remove hits.
        communicatorService.$emit('hits', {"hits" : {}});
      }
    };

    /**
     * Check that a given interval is valid and search.
     *
     * Use on change on the input fields.
     *
     * @param interval
     *   The name of the interval.
     */
    $scope.intervalCheck = function intervalCheck(interval) {
      var current = $scope.query.intervals[interval];

      // Check that from and to exists.
      if (!current.hasOwnProperty('from') || current.from === '') {
        return;
      }

      if (!current.hasOwnProperty('to') || current.to === '') {
        return;
      }

      // Test that from is smaller than to.
      if (current.from >= current.to) {
        return;
      }

      // Update search result.
      resetPager();
      search();
    };

    /**
     * Check that a given interval is valid and search.
     *
     * Use on change on the input fields.
     *
     * @param date
     *   The name of the date.
     */
    $scope.dateCheck = function dateCheck(date) {

      // Check that from and to exists.
      if (!date.hasOwnProperty('from') || date.from === '') {
        return;
      }

      if (!date.hasOwnProperty('to') || date.to === '') {
        return;
      }

      // Test that from is smaller than to.
      if (date.from > date.to) {
        return;
      }

      // Update search result.
      resetPager();
      search();
    };

    // Get set show on the road.
    init();
  }
]);
