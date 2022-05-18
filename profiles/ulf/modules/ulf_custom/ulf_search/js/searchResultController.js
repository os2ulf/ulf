/**
 * @file
 * This is the controller for the search result application.
 *
 * It simply updates the view when hits have been received.
 */

angular.module('searchResultApp').controller('UlfResultController', ['CONFIG', 'communicatorService', '$scope',
  function (CONFIG, communicatorService, $scope) {
    'use strict';

    // Set template to use.
    $scope.template = CONFIG.templates.result;

    // Scope variable that can be used to make indications on the current
    // process. E.g display spinner.
    $scope.searching = false;

    // Check if the provider supports an pager.
    if (CONFIG.provider.hasOwnProperty('pager')) {
      // Add pager information to the scope.
      $scope.pager = angular.copy(CONFIG.provider.pager);
    }

    /**
     * Update pager information.
     */
    $scope.search = function search() {
      var pager = angular.copy($scope.pager);
      pager.page--;
      communicatorService.$emit('pager', pager);
    };

    /**
     * Handled search results hits from the search box application.
     */
    $scope.hits = [];
    communicatorService.$on('hits', function onHits(event, data) {
      var phase = this.$root.$$phase;
      if(CONFIG.provider.index === "54894398a98f973ec6a24936b72d3bf4" ||
         CONFIG.provider.index === "e8d9bfcd61212f6d4b3c23ff6addd25b") {
        // hacky rewrite to accomodate the different design on
        // the result page for ungegarantien.dk/udbydere
        var alphabet = {};
        for (let i = 0; i < data.hits.results.length; i++) {
          let char = data.hits.results[i].field_profile_name.charAt(0).toUpperCase();
          if(!alphabet.hasOwnProperty(char)) {
            alphabet[char] = [];
          }
          alphabet[char].push(data.hits.results[i]);
        }
        $scope.alphabet = alphabet;
      }
      if (phase === '$apply' || phase === '$digest') {
        $scope.hits = data.hits;
        $scope.pager = data.pager;
        $scope.pager.page++;
        $scope.searching = false;
      }
      else {
        $scope.$apply(function () {
          $scope.hits = data.hits;
          $scope.pager = data.pager;
          $scope.pager.page++;
          $scope.searching = false;
        });
      }
    });

    /**
     * Handled searching message, send when search is called.
     */
    communicatorService.$on('searching', function onSearching(event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.searching = true;
      }
      else {
        $scope.$apply(function () {
          $scope.searching = true;
        });
      }
    });

    /**
     * Handled pager updates.
     */
    communicatorService.$on('pager', function onPager(event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.pager = data;
      }
      else {
        $scope.$apply(function () {
          $scope.pager = data;
        });
      }
    });
  }
]);
