/**
 * Modify several aspects of the frontend application form.
 **/
(function ($) {
  "use strict";
  Drupal.behaviors.transportpulje_form = {
    attach: function (context, settings) {

      // When the select course dropdown is changed we alter the address fields.
      $('.form-item-course-dropdown').change(function () {
        var value = $('.form-item-course-dropdown .chosen-single span').html();
        var nid = $('.form-item-course-dropdown option').filter(function() {
          return ($(this).text() === value)
        }).val();
        // Check if address is not hidden for selected for node. (Not in hidden array)
        // If so, apply address else act as the course had no address.
        // If address is not in hidden array.
        if (nid) {
          if (settings.transportpulje_form.hidden.indexOf(nid) < 0) {
            $('#course_dropdown_address').load('fetch-address/' + nid, function () {
              if ($(this)[0].innerHTML.length === 0) {
                // When a course without address but not hidden is selected.
                $('#edit-course-not-found').prop('checked', false).trigger('change');
                resetFields();
              }
              else {
                // When a course with address is selected.
                $('#edit-course-not-found').prop('checked', false).trigger('change');
                populateFields(this);
              }
            });
          }
        }
        else {
          // Act as if address was hidden/ Had no address
          $('#edit-course-not-found').prop('checked', false).trigger('change');
          resetFields();
        }
      });

      // When no course found checkbox is clicked we alter course dropdown and address fields.
      $('#edit-course-not-found').click(function () {
        if ($(this).is(':checked')) {
          // Clear all fields in part one.
          $('.form-item-course-dropdown .chosen-single').html('<span>- Vælg -</span>');
          $('.form-item-course-dropdown .result-selected').removeClass('result-selected');
          $('#edit-select-course .form-type-textarea textarea').val('');
          $('#edit-select-course .form-type-textfield input').val('');
        }
        else {
          $('#edit-select-course .form-type-textarea textarea').val('');
          $('#edit-select-course .form-type-textfield input').val('');
        }
      });

      // When course is loaded with url parameter. And it's the first page load.
      var url_course_id = urlParam('course_id');
      if (url_course_id && !(0 in context)) {
        $('#course_dropdown_address').load('fetch-address/' + url_course_id, function () {
          if ($(this)[0].innerHTML.length == 0) {
            resetFields()
          }
          else {
            populateFields(this);
          }
        });
      }

      // Setup dropdown lists.
      var inst_by_type = [];
      inst_by_type['school_options'] = '';
      inst_by_type['kindergarten_options'] = '';
      inst_by_type['nursery_options'] = '';
      inst_by_type['daycare_options'] = '';

      // Sort the institution dropdown list.
      var sort_arr = [];
      for (var key in settings.transportpulje_form.institutions) {
        sort_arr.push(settings.transportpulje_form.institutions[key]);
      }
      var sorted = sort_arr.sort(function (a,b) {
        var nameA = a.name.toLowerCase(), nameB = b.name.toLowerCase();
        if (nameA < nameB) {
          return -1;
        }
        if (nameA > nameB) {
          return 1;
        }
        return 0;
      });

      // Populate institutions dropdown lists.
      $.each(sorted, function(index, value) {
        if (typeof value.field_tpf_type.und !== 'undefined') {
          switch (value.field_tpf_type.und['0'].value) {
            case 'tpf_institution_type_school':
              inst_by_type.school_options += '<option value="'+ value.tid + '">' + value.name + '</option>';
              break;

            case 'tpf_institution_type_kindergarten':
              inst_by_type.kindergarten_options += '<option value="'+ value.tid + '">' + value.name + '</option>';
              break;

            case 'tpf_institution_type_nursery':
              inst_by_type.nursery_options += '<option value="'+ value.tid + '">' + value.name + '</option>';
              break;

            case 'tpf_institution_type_daycare':
              inst_by_type.daycare_options += '<option value="'+ value.tid + '">' + value.name + '</option>';
              break;
          }
        }
      });

      // Remove dash before child items in institutions dropdown list.
      // We reduce a nested list to flat list so we don't want it.
      $('.form-item-institution-name option:not(:first-child)').text(
        function() {
          return this.text.replace('-', '');
        }
      );

      // Change the result of the institutions dropdown based on type selected.
      $('.form-item-institution-type').change(function (){
        var inst_type = $('.form-item-institution-type').find(":selected").text();
        switch (inst_type) {
          case 'Skole':
            $('.form-item-institution-name #edit-institution-name').html(inst_by_type.school_options);
            break;

          case 'Børnehave':
            $('.form-item-institution-name #edit-institution-name').html(inst_by_type.kindergarten_options);
            break;

          case 'Vuggestue':
            $('.form-item-institution-name #edit-institution-name').html(inst_by_type.nursery_options);
            break;

          case 'Dagplejer':
            $('.form-item-institution-name #edit-institution-name').html(inst_by_type.daycare_options);
            break;
        }
      });

      // Empty address fields. Helper function.
      function resetFields() {
        $('#edit-street').val('');
        $('#edit-postal-code').val('');
        $('#edit-city').val('');
      }

      // Populate address fields. Helper function.
      function populateFields(element) {
        $('#edit-street').val($(element).find('#course_dropdown_street')[0].innerHTML);
        $('#edit-postal-code').val($(element).find('#course_dropdown_postal')[0].innerHTML);
        $('#edit-city').val($(element).find('#course_dropdown_city')[0].innerHTML);
      }

      // Find url parameters helper function.
      function urlParam(name){
        var results = new RegExp('[\?&]' + name + '=([^]*)').exec(window.location.href);
        if (results == null) {
          return null;
        }
        else {
          return results[1] || 0;
        }
      }
    }
  };
}(jQuery));

