/**
 * @file
 * Logic for the node form.
 *
 * A lot of fields change due to the selection of the target group field.
 */
(function ($) {

  // Array to hold subgroup checkboxes
  var subgroup = [];

  /**
   * Initialize the form by hiding elements and attaching event handlers.
   */
  function initializeFormElements() {
    // Hide all target subgroups.
    $('.field-name-field-target-group-sub input').parent().hide();

    // Hide filter selections.
    $('.filter-wrapper').hide();

    // Hide specific fields only relevant for certain target groups.
    // $('.field-name-field-post-work').hide();
    if (typeof Drupal.settings.primary_target_group == 'undefined') {
      $('.field-name-field-educational-goals').hide();
    }
    $('.field-name-field-subjects-primary-school').hide();
    $('.field-name-field-subjects-youth').hide();
    $('.node-course-form .field-name-field-educational-material').hide();
    $('.node-course-form .field-name-field-inspirational-material').hide();
    $('.field-name-field-practical-info-buttons').hide();

    // $('.field-name-field-material-suggestions').hide();

    // Used in field help text.
    $('.is-school').hide();
    $('.is-preschool').hide();

    // Listen to change event on "target group" radio buttons in edit user
    // form and change form content based on the selection. This is also
    // called directly to be initialized on load.
    $('.field-name-field-target-group').change(function() {
      targetGroupSelectionChanged(true);
    });
    targetGroupSelectionChanged(false);

    // When "Full year" is unchecked show field group for duration else hide
    // the fields. This is also called when the form is initialized.
    var timeSelector = $('.field-name-field-period-full-year');
    timeSelector.change(function () {
      timePeriodSelectionChanged(timeSelector)
    });
    timePeriodSelectionChanged(timeSelector);

    // Handle the price (free) checkboxes and show/hide price input fields
    // based on free field state.
    var priceSelector = $('.field-name-field-free');
    priceSelector.click(function () {
      priceChanged(priceSelector)
    });
    priceChanged(priceSelector);

    // Hide empty fields for old price and and contact on course educators
    // content type.
    // If fields have values the editor should manually move them. When all
    // values have been moved the field should be deleted as part of a
    // future patch. @TODO: This is still awaiting manual transfer of price
    // field to field collection.
    if (!$('.field-name-field-course-contact-name input').val()) {
      $('.field-name-field-course-contact-name').hide();
    }
    if (!$('.field-name-field-course-contact-mail input').val()) {
      $('.field-name-field-course-contact-mail').hide();
    }
    if (!$('.field-name-field-course-phone input').val()) {
      $('.field-name-field-course-phone ').hide();
    }

    // Hides the price field outside the field collection wrapper if it is
    // set to 0 so editors will not be confused.
    if ($('.fieldset-wrapper > .field-name-field-price input').val() == '0' || $('.fieldset-wrapper > .field-name-field-price input').val() == '0.00' || !$('.fieldset-wrapper > .field-name-field-price input').val()) {
      $('.fieldset-wrapper > .field-name-field-price').hide();
    }
  }

  /**
   * Displays/hides Target Subgroup divs according to the callback function.
   *
   * @param {function} accept_callback
   *   The function that decided if the text is accepted or rejected.
   */
  function displayRelevantSubgroupByKeyword(accept_callback) {
    // Iterate each subgroup input.
    $.each(subgroup, function (index, arr) {
      var text = arr[0];
      var value = arr[1];

      // If the accept_callback, accepts the text show the input, else hide
      // and uncheck the field.
      var field = $('.field-name-field-target-group-sub input[value=' + value + ']');
      if (accept_callback(text)) {
        field.parent().show();
      }
      else {
        field.prop("checked", false);
      }
    });
  }

  /**
   * Sets up available fields when Preschool is selected.
   */
  function selectionPreschool(onChange) {
    // The sub target group field selection values.
    displayRelevantSubgroupByKeyword(function (text) {
      return text.indexOf('år') !== -1 || text.indexOf('Børn og unge med særlige behov') !== -1;
    });

    $('.field-name-field-inspirational-material').show();
    $('.field-name-field-material-suggestions').show();
    if (typeof Drupal.settings.primary_target_group == 'undefined') {
      $('.field-name-field-educational-goals').show();
    }
    $('.field-name-field-practical-info-buttons').show();
    $('.is-preschool').show();

    // setLabel('field-background-knowledge', 'Forberedelse');

    clearSubjectsValues('subjects-primary-school');
    clearSubjectsValues('subjects-youth');

    if (onChange) {
      // clearCKEditorTextAreaValue('activities');
      // clearCKEditorTextAreaValue('background-knowledge');
      // clearCKEditorTextAreaValue('post-work');
    }
  }

  /**
   * Sets up available fields when Primary School is selected.
   */
  function selectionPrimarySchool(onChange) {
    // The sub target group field selection values.
    displayRelevantSubgroupByKeyword(function (text) {
      return text.indexOf('klasse') !== -1 || text.indexOf('DUS') !== -1 || text.indexOf('Børn og unge med særlige behov') !== -1;
    });

    $('.field-name-field-post-work').show();
    $('.field-name-field-educational-material').show();
    $('.field-name-field-subjects-primary-school').show();
    $('.field-name-field-practical-info-buttons').show();
    $('.is-school').show();

    // setLabel('field-background-knowledge', 'Forberedelse');

    clearSubjectsValues('subjects-youth');
    if (typeof Drupal.settings.primary_target_group == 'undefined') {
      clearSubjectsValues('educational-goals');
    }

    if (onChange) {
      // clearCKEditorTextAreaValue('activities');
      // clearCKEditorTextAreaValue('background-knowledge');
      // clearCKEditorTextAreaValue('post-work');
    }
  }

  /**
   * Sets up available fields when Youth is selected.
   */
  function selectionYouth(onChange) {
    // The sub target group field selection values.
    displayRelevantSubgroupByKeyword(function (text) {
      return (text.indexOf('år') === -1 && text.indexOf('klasse') === -1 && text.indexOf('DUS') === -1);
    });

    $('.field-name-field-post-work').show();
    $('.field-name-field-educational-material').show();
    $('.field-name-field-subjects-youth').show();
    $('.is-school').show();


    // setLabel('field-background-knowledge', 'Forberedelse');

    clearSubjectsValues('subjects-primary-school');
    if (typeof Drupal.settings.primary_target_group == 'undefined') {
      clearSubjectsValues('educational-goals');
      clearSubjectsValues('practical-info-buttons');
    }

    if (onChange) {
      // clearCKEditorTextAreaValue('activities');
      // clearCKEditorTextAreaValue('background-knowledge');
      // clearCKEditorTextAreaValue('post-work');
    }
  }

  /**
   * Clear subjects and educational goals field field values.
   */
  function clearSubjectsValues(fieldValue) {
    $('.field-name-field-' + fieldValue + ' input').prop("checked", false);
  }

  /**
   * Clear subjects and educational goals field field values.
   */
  function clearCKEditorTextAreaValue(fieldValue) {
    // Create the name of the CKEditor field.
    var ckeditor_field_name = 'edit-field-' + fieldValue + '-und-0-value';

    // Get the CKEDITOR instance and empty the field.
    var instance = CKEDITOR.instances[ckeditor_field_name];
    if (instance) {
      instance.setData('');
      $('.field-name-field-' + fieldValue + ' textarea').val('');
    }
  }

  /**
   * Handle logic when Target Group selector is changed.
   */
  function targetGroupSelectionChanged(onChange) {
    // Hide all target groups.
    $('.field-name-field-target-group-sub input').parent().hide();

    // Hide specific fields only relevant for certain target groups.
    // $('.field-name-field-post-work').hide();
    $('.field-name-field-post-work').show();

    if (typeof Drupal.settings.primary_target_group == 'undefined') {
      $('.field-name-field-educational-goals').hide();
    }
    $('.field-name-field-subjects-primary-school').hide();
    $('.field-name-field-subjects-youth').hide();
    $('.node-course-form .field-name-field-educational-material').hide();
    $('.node-course-form .field-name-field-inspirational-material').hide();
    $('.field-name-field-practical-info-buttons').hide();
    // $('.field-name-field-material-suggestions').hide();

    // Used in field help text.
    $('.is-school').hide();
    $('.is-preschool').hide();

    // Fill the subgroup array, if no already done. Used in the
    // sub-selection function in the switch statement below.
    if (subgroup.length === 0) {
      $('.field-name-field-target-group-sub .option').each(function () {
        var val = $(this).siblings('input').val();
        var text = $(this).text();
        subgroup.push([text, val]);
      });
    }

    // Change form input elements based on selected target group.
    var selected = $(':checked', $('.field-name-field-target-group')).next().text().trim();
    switch (selected) {
      case 'Dagtilbud':
        selectionPreschool(onChange);
        break;

      case 'Grundskole':
        selectionPrimarySchool(onChange);
        break;

      case 'Ungdomsuddannelse':
        selectionYouth(onChange);
        break;

      default:
        // When the edit node page is first loaded (for new nodes) the
        // selection is empty and we fallback to "pre-school".
        // This should not happen - ever.
        selectionPreschool(onChange);
        break;
    }
  }

  /**
   * Hide/show the time period selection fields.
   *
   * @param {object} field
   *   jQuery element object.
   */
  function timePeriodSelectionChanged(field) {
    var field_period = $('.field-name-field-period');
    if ($(':checked', field).length) {
      field_period.hide();
      $('.start-date-wrapper input', field_period).val('');
      $('.end-date-wrapper input', field_period).val('');
    }
    else {
      // When the field time period is hidden/displayed when "full year" it
      // toggled the data fields is reset and pre-filled.
      var date = new Date();
      var start_date = ('0' + date.getDate()).slice(-2) + '/'
        + ('0' + (date.getMonth() + 1)).slice(-2) + '/'
        + date.getFullYear();
      var time = ('0' + date.getHours()).slice(-2) + ':' + ('0' + date.getMinutes()).slice(-2);

      field_period.show();
      $('.start-date-wrapper input:first', field_period).val(start_date);
      $('.start-date-wrapper input:last', field_period).val(time);
      $('.end-date-wrapper input:first', field_period).val('01/01/2030');
      $('.end-date-wrapper input:last', field_period).val(time);
    }
  }

  /**
   * Hide/show the price fields.
   *
   * @param {object} field
   *   jQuery element object.
   */
  function priceChanged(field) {
    if ($(':checked', field).length) {
      $('.field-name-field-collection-price').hide();
      $('.field-name-field-vary-price').hide();
      $('.field-name-field-price input').val('');
      $('.field-name-field-moms select').val('_none');
      $('.field-name-field-unit-price select').val('_none');
      $('.form-item-field-practical-info-buttons-und-show-free-course-request input').prop("checked", false).prop("disabled", true);
    }
    else {
      $('.field-name-field-collection-price').show();
      $('.field-name-field-vary-price').show();
      $('.form-item-field-practical-info-buttons-und-show-free-course-request input').prop("disabled", false);
    }
  }

  /**
   * Change label for form elements.
   *
   * @param fieldName
   *   The field for which to change label
   * @param labelNew
   *   The new value for the label
   *
   */
  function setLabel(fieldName, labelNew) {
    $('#edit-' + fieldName + ' label').html(labelNew);
  }

  $(function() {
    // Get the show on the road.
    initializeFormElements();
  });

}(jQuery));
