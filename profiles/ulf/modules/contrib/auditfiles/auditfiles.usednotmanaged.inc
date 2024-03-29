<?php

/**
 * @file
 * Generates a report showing files in file_usage, but not in file_managed.
 */

/**
 * The following are functions for displaying the list of files on the page.
 */

/**
 * Generates the report.
 *
 * This cannot be sorted, because a result set that is too large will time out.
 *
 * @param array $form
 *   The form definition.
 * @param array $form_state
 *   The current state of the form.
 *
 * @return array
 *   The form definition.
 */
function auditfiles_used_not_managed_form(array $form, array &$form_state) {
  // Check to see if the confirmation form needs to be displayed instead of the
  // normal form.
  if (isset($form_state['storage']['confirm'])) {
    return _auditfiles_used_not_managed_confirm_operation($form, $form_state);
  }

  // Get the records to display.
  // Check to see if there is saved data, and if so, use that.
  $rows = variable_get('auditfiles_used_not_managed_files_to_display', array());
  if (empty($rows)) {
    // The data is not saved and the batch operation has not been run, so get
    // the data using the default options.
    $file_ids = _auditfiles_used_not_managed_get_file_list();
    if (!empty($file_ids)) {
      foreach ($file_ids as $file_id) {
        $rows[$file_id] = _auditfiles_used_not_managed_get_file_data($file_id);
      }
    }

    // Save the data for persistent use.
    variable_set('auditfiles_used_not_managed_files_to_display', $rows);
  }

  // Set up the pager.
  if (!empty($rows)) {
    $items_per_page = variable_get('auditfiles_report_options_items_per_page', 50);
    if (!empty($items_per_page)) {
      $current_page = pager_default_initialize(count($rows), $items_per_page);
      // Break the total data set into page sized chunks.
      $pages = array_chunk($rows, $items_per_page, TRUE);
    }
  }

  // Define the form.
  // Setup the record count and related messages.
  $maximum_records = variable_get('auditfiles_report_options_maximum_records', 250);
  if (!empty($rows)) {
    if ($maximum_records > 0) {
      $file_count_message = 'Found at least @count files in the file_usage table that are not in the file_managed table.';
    }
    else {
      $file_count_message = 'Found @count files in the file_usage table that are not in the file_managed table.';
    }
    $form_count = format_plural(
      count($rows),
      'Found 1 file in the file_usage table that is not in the file_managed table.',
      $file_count_message
    );
  }
  else {
    $form_count = t('Found no files in the file_usage table that are not in the file_managed table.');
  }

  // Add the button to reset the record selection.
  $form['reset_records'] = array(
    '#type' => 'submit',
    '#value' => t('Reset file list'),
    '#suffix' => '<div>' . t("Use this button to reset this report's variables and load the page anew.") . '</div>',
  );
  // Add the button to batch process the list of results.
  if ($maximum_records > 0) {
    $form['batch_process'] = array(
      '#type' => 'submit',
      '#value' => t('Load all files'),
      '#suffix' => '<div>' . t('Use this button to load the number of records specified with the "Batch size" administrative configuration setting.') . '</div>',
    );
  }

  // Create the form table.
  $form['files'] = array(
    '#type' => 'tableselect',
    '#header' => _auditfiles_used_not_managed_get_header(),
    '#empty' => t('No items found.'),
    '#prefix' => '<div><em>' . $form_count . '</em></div>',
  );

  // Add the data.
  if (!empty($rows) && !empty($pages)) {
    $form['files']['#options'] = $pages[$current_page];
  }
  elseif (!empty($rows)) {
    $form['files']['#options'] = $rows;
  }
  else {
    $form['files']['#options'] = array();
  }

  // Add any action buttons.
  if (!empty($rows)) {
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Delete selected items from the file_usage table'),
    );

    // Add the pager.
    $form['pager'] = array('#markup' => theme('pager'));
  }

  return $form;
}

/**
 * Submit handler for the auditfiles_used_not_managed_form form.
 */
function auditfiles_used_not_managed_form_submit($form, &$form_state) {
  // Check if an operation was performed.
  if (!empty($form_state['values']['op'])) {
    // Check which operation was performed and start the batch process.
    if ($form_state['values']['op'] == t('Load all files')) {
      // Clear the variable, so subsequent pages will load the correct data.
      variable_del('auditfiles_used_not_managed_files_to_display');
      // Prepare and set the batch.
      batch_set(_auditfiles_used_not_managed_batch_display_create_batch());
    }
    elseif ($form_state['values']['op'] == t('Reset file list')) {
      // Reset all the variables for this report, so subsequent pages loads will
      // load and use the correct data.
      db_delete('variable')
        ->condition('name', 'auditfiles_used_not_managed_%', 'LIKE')
        ->execute();
      cache_clear_all('variables', 'cache_bootstrap');
    }
    elseif ($form_state['values']['op'] == t('Delete selected items from the file_usage table')
      && !empty($form_state['values']['files'])) {
      foreach ($form_state['values']['files'] as $file_id) {
        if (!empty($file_id)) {
          // At least one file was selected, and the operation has not been
          // confirmed, so modify the data to display the confirmation form.
          $form_state['storage']['files'] = $form_state['values']['files'];
          $form_state['storage']['op'] = $form_state['values']['op'];
          $form_state['storage']['confirm'] = TRUE;
          $form_state['rebuild'] = TRUE;
          return TRUE;
        }
      }

      drupal_set_message(t('No items were selected to operate on.'));
    }
    elseif ($form_state['values']['op'] == t('Yes')) {
      if ($form_state['values']['operation'] == 'delete') {
        // Prepare and set the batch.
        batch_set(_auditfiles_used_not_managed_batch_delete_create_batch($form_state['values']['changelist']));
      }
    }
  }
}

/**
 * The following are functions that are common for all batches in this file.
 */

/**
 * Adds vaules to a batch definition that are common to all batches in the file.
 *
 * @return array
 *   The beginning of the batch definition.
 */
function _auditfiles_used_not_managed_batch_set_common_values() {
  return array(
    'error_message' => t('One or more errors were encountered processing the files.'),
    'file' => drupal_get_path('module', 'auditfiles') . '/auditfiles.usednotmanaged.inc',
    'finished' => '_auditfiles_used_not_managed_batch_finish_batch',
    'progress_message' => t('Completed @current of @total operations.'),
  );
}

/**
 * The function that is called when the batch is complete.
 */
function _auditfiles_used_not_managed_batch_finish_batch($success, $results, $operations) {
  if ($success) {
    if (!empty($results['files_to_display'])) {
      // Save the gathered data for display.
      variable_set('auditfiles_used_not_managed_files_to_display', $results['files_to_display']);
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(
      t('An error occurred while processing @operation with arguments : @args',
        array(
          '@operation' => $error_operation[0],
          '@args' => print_r($error_operation[0], TRUE),
        )
      )
    );
  }
}

/**
 * The following are functions for preparing the batch for displaying the files.
 */

/**
 * Prepares the definition for the page display batch.
 *
 * @return array
 *   The batch definition.
 */
function _auditfiles_used_not_managed_batch_display_create_batch() {
  $batch = _auditfiles_used_not_managed_batch_set_common_values();
  $batch['title'] = t('Loading file audit data');
  $batch['operations'] = _auditfiles_used_not_managed_batch_display_get_operations();
  return $batch;
}

/**
 * Configures the operations for the batch process.
 *
 * @return array
 *   The operations to execute.
 */
function _auditfiles_used_not_managed_batch_display_get_operations() {
  $operations = array();
  $operations[] = array(
    '_auditfiles_used_not_managed_batch_display_get_files',
    array(),
  );
  $operations[] = array(
    '_auditfiles_used_not_managed_batch_display_process_files',
    array(),
  );
  return $operations;
}

/**
 * The batch process operation for getting the files.
 *
 * @param array $context
 *   Used by the Batch API to keep track of and pass data from one operation to
 *   the next.
 */
function _auditfiles_used_not_managed_batch_display_get_files(array &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_file'] = 0;
    $query = 'SELECT COUNT(DISTINCT fid) FROM {file_usage} fu WHERE fid NOT IN (SELECT fid FROM {file_managed})';
    $record_count = db_query($query)->fetchField();
    $batch_size = variable_get('auditfiles_report_options_batch_size', 1000);
    if ($batch_size > 0 && $record_count > $batch_size) {
      $context['sandbox']['max'] = $batch_size;
    }
    else {
      $context['sandbox']['max'] = $record_count;
    }
  }
  if (empty($context['results']['file_list'])) {
    $context['results']['file_list'] = array();
  }

  // Get the file data from the database.
  // This cannot be sorted any other way here, or the results are not complete.
  $query = 'SELECT fid
    FROM {file_usage}
    WHERE fid NOT IN (SELECT fid FROM {file_managed})
      AND fid > :fid
    ORDER BY fid ASC
    LIMIT 20';
  $files = db_query($query, array(':fid' => $context['sandbox']['current_file']))->fetchAll();

  foreach ($files as $file) {
    $context['results']['file_list'][$file->fid] = $file->fid;

    // Update the progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_file'] = $file->fid;
    $context['message'] = t(
      'Getting the list of files. Processed file @num1 of @num2. Last file ID processed: !file_id.',
      array(
        '@num1' => $context['sandbox']['progress'],
        '@num2' => $context['sandbox']['max'],
        '!file_id' => $file->fid,
      )
    );
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * The batch process operation for formatting the files for display on the page.
 *
 * @param array $context
 *   Used by the Batch API to keep track of and pass data from one operation to
 *   the next.
 */
function _auditfiles_used_not_managed_batch_display_process_files(array &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    if (empty($context['results']['file_list'])) {
      $context['sandbox']['progress'] = 1;
      $context['sandbox']['max'] = 1;
    }
    else {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['max'] = count($context['results']['file_list']);
    }
  }
  if (empty($context['results']['files_to_display'])) {
    $context['results']['files_to_display'] = array();
  }

  if (!empty($context['results']['file_list'])) {
    $file_list = array_slice($context['results']['file_list'], 0, 20, TRUE);

    $query = 'SELECT fid, module, type, id, count
      FROM {file_usage}
      WHERE fid IN (:file_list)';
    $files_list = db_query($query, array(':file_list' => $file_list))->fetchAll();

    foreach ($files_list as $file) {
      $context['results']['files_to_display'][$file->fid] = array(
        'fid' => $file->fid,
        'module' => $file->module . ' ' . t('module'),
        'id' => l($file->type . '/' . $file->id, $file->type . '/' . $file->id),
        'count' => $file->count,
      );

      unset($context['results']['file_list'][$file->fid]);

      // Update the progress information.
      $context['sandbox']['progress']++;
      $context['message'] = t(
        'Processing the file list. Processed file @num1 of @num2. Last file ID processed: !file_id.',
        array(
          '@num1' => $context['sandbox']['progress'],
          '@num2' => $context['sandbox']['max'],
          '!file_id' => $file->fid,
        )
      );
    }
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
}

/**
 * The following are functions for the batch delete operation.
 */

/**
 * Presents a confimation form to verify the user wants to complete the action.
 *
 * @param array $form
 *   The form definition.
 * @param array $form_state
 *   The current state of the form.
 *
 * @return array
 *   A form array for a confirmation form.
 */
function _auditfiles_used_not_managed_confirm_operation(array $form, array &$form_state) {
  $values = $form_state['values'];

  $form['changelist'] = array(
    '#prefix' => '<ul>',
    '#suffix' => '</ul>',
    '#tree' => TRUE,
  );

  // Prepare the list of items to present to the user.
  if (!empty($values['files'])) {
    foreach ($values['files'] as $file_id) {
      if (!empty($file_id)) {
        $form['changelist'][$file_id] = array(
          '#type' => 'hidden',
          '#value' => $file_id,
          '#prefix' => '<li>' . t('File ID') . ' <strong>' . $file_id . '</strong> ' . t('will be deleted from the file_usage table.'),
          '#suffix' => "</li>\n",
        );
      }
      else {
        // Unsetting the unprocessed files prevents confirm_submit from dealing
        // with them.
        unset($form_state['values']['files'][$file_id]);
      }
    }
  }

  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => 'delete',
  );

  // Tell the submit handler to process the confirmation.
  $form['process'] = array(
    '#type' => 'hidden',
    '#value' => 'TRUE',
  );
  // Go back to the main form, when done with this one.
  $form['destination'] = array(
    '#type' => 'hidden',
    '#value' => 'admin/reports/auditfiles/usednotmanaged',
  );

  return confirm_form(
    $form,
    t('Delete these items from the file_usage table?'),
    'admin/reports/auditfiles/usednotmanaged',
    '<strong>' . t('This action cannot be undone.') . '</strong>',
    t('Yes'),
    t('No')
  );
}

/**
 * Creates the batch for deleting files from the file_usage table.
 *
 * @param array $fileids
 *   The list of file IDs to be processed.
 *
 * @return array
 *   The definition of the batch.
 */
function _auditfiles_used_not_managed_batch_delete_create_batch(array $fileids) {
  $batch = _auditfiles_used_not_managed_batch_set_common_values();
  $batch['title'] = t('Deleting files from the file_usage table');
  $operations = array();
  // Remove all the empty values from the array.
  $file_ids = array();
  foreach ($fileids as $file_id) {
    if ($file_id != 0) {
      $file_ids[] = $file_id;
    }
  }
  // Fill in the $operations variable.
  foreach ($file_ids as $file_id) {
    $operations[] = array(
      '_auditfiles_used_not_managed_batch_delete_process_batch',
      array($file_id),
    );
  }
  $batch['operations'] = $operations;
  return $batch;
}

/**
 * The batch process for deleting the file.
 *
 * @param int $file_id
 *   The ID of a file to delete.
 * @param array $context
 *   Used by the Batch API to keep track of and pass data from one operation to
 *   the next.
 */
function _auditfiles_used_not_managed_batch_delete_process_batch($file_id, array &$context) {
  // Process the current file.
  _auditfiles_used_not_managed_batch_delete_process_file($file_id);
  // The contents of 'results' are available as $results in the 'finished'
  // function.
  $context['results'][] = $file_id;
  // Set a progress message.
  $context['message'] = t('Processed file ID %file_id.', array('%file_id' => $file_id));
}

/**
 * Deletes the specified file from the file_usage table.
 *
 * @param int $file_id
 *   The ID of the file to delete from the database.
 */
function _auditfiles_used_not_managed_batch_delete_process_file($file_id) {
  $num_rows = db_delete('file_usage')
    ->condition('fid', $file_id)
    ->execute();
  if (empty($num_rows)) {
    drupal_set_message(
      t(
        'There was a problem deleting the record with file ID %fid from the file_usage table. Check the logs for more information.',
        array('%fid' => $file_id)
      ),
      'warning'
    );
  }
  else {
    // Remove the deleted files from the list of files to display.
    $rows = variable_get('auditfiles_used_not_managed_files_to_display', array());
    unset($rows[$file_id]);
    variable_set('auditfiles_used_not_managed_files_to_display', $rows);
  }
}

/**
 * The following are functions for retrieving and processing the file data.
 */

/**
 * Retrieves the file IDs to operate on.
 *
 * @return array
 *   The file IDs.
 */
function _auditfiles_used_not_managed_get_file_list() {
  // Get all the file IDs in the file_usage table that are not in the
  // file_managed table.
  $query = 'SELECT DISTINCT fid FROM {file_usage} fu WHERE fid NOT IN (SELECT fid FROM {file_managed})';

  // If record limition has been configured, only use those records within that
  // specification.
  $maximum_records = variable_get('auditfiles_report_options_maximum_records', 250);
  if ($maximum_records > 0) {
    $query .= ' LIMIT ' . $maximum_records;
  }

  return db_query($query)->fetchCol();
}

/**
 * Retrieves information about an individual file from the database.
 *
 * @param int $file_id
 *   The ID of the file to prepare for display.
 *
 * @return array
 *   The row for the table on the report, with the file's information formatted
 *   for display.
 */
function _auditfiles_used_not_managed_get_file_data($file_id) {
  // Get the file information for the specified file ID from the database.
  $query = 'SELECT * FROM {file_usage} WHERE fid = ' . $file_id;
  $file = db_query($query)->fetchObject();
  // Prepare the file information for displaying on the page. If the file exists
  // on the server, this will be an empty array, and it can be ignored.
  return array(
    'fid' => $file->fid,
    'module' => $file->module . ' ' . t('module'),
    'id' => l($file->type . '/' . $file->id, $file->type . '/' . $file->id),
    'count' => $file->count,
  );
}

/**
 * The following are helper functions.
 */

/**
 * Returns the header to use for the display table.
 *
 * @return array
 *   The header to use.
 */
function _auditfiles_used_not_managed_get_header() {
  return array(
    'fid' => array(
      'data' => t('File ID'),
    ),
    'module' => array(
      'data' => t('Used by'),
    ),
    'id' => array(
      'data' => t('Used in'),
    ),
    'count' => array(
      'data' => t('Count'),
    ),
  );
}
