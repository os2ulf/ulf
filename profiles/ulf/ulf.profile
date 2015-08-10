<?php

/**
 * Implement hook_install_tasks_alter().
 *
 */
function ulf_install_tasks_alter(&$tasks, $install_state) {
  // Callback for language selection.
  $tasks['install_select_locale']['function'] = 'ulf_locale_selection';

  // Enable custom wysiwyg module.
  if ($install_state['active_task'] == 'install_finished') {
    module_enable(array('ulf_wysiwyg'));
  }
}

// Set default language to english.
function ulf_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'Ulf';
    $form['server_settings']['site_default_country']['#default_value'] = 'DK';
    $form['server_settings']['date_default_timezone']['#default_value'] = 'Europe/Copenhagen';
  }
}

/**
 * Implements hook_install_tasks().
 *
 * As this function is called early and often, we have to maintain a cache or
 * else the task specifying a form may not be available on form submit.
 */
function ulf_install_tasks(&$install_state) {
  $ret = array(
    // Update translations.
    'ulf_import_translation' => array(
      'display_name' => st('Set up translations'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),
    'ulf_setup_filter_and_wysiwyg' => array(
      'display_name' => st('Setup filter and WYSIWYG'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch'
    ),
  );
  return $ret;
}

/**
 * Translation callback.
 *
 * Add danish language and import for every module.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return array
 *   List of batches.
 */
function ulf_import_translation() {
  // Enable danish language.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  locale_add_language('da', NULL, NULL, NULL, '', NULL, TRUE, TRUE);

  // Build batch with l10n_update module.
  $history = l10n_update_get_history();
  module_load_include('check.inc', 'l10n_update');
  $available = l10n_update_available_releases();
  $updates = l10n_update_build_updates($history, $available);

  // Fire of the batch!
  module_load_include('batch.inc', 'l10n_update');
  $updates = _l10n_update_prepare_updates($updates, NULL, array());
  $batch = l10n_update_batch_multiple($updates, LOCALE_IMPORT_KEEP);
  return $batch;
}

/**
 * Setup text filter and WYSIWYG.
 */
function ulf_setup_filter_and_wysiwyg() {
  $format = new Stdclass();
  $format->format = 'full_html';
  $format->name = 'Full html';
  $format->status = 1;
  $format->weight = 0;
  $format->filters = array();

  filter_format_save($format);


  $format = new Stdclass();
  $format->format = 'editor';
  $format->name = 'Editor';
  $format->status = 1;
  $format->weight = 0;
  $format->filters = array(
    'filter_url' => array(
      'weight' => -49,
      'status' => 1,
      'settings' => array(
        'filter_url_length' => 72,
      ),
    ),
    'filter_html' => array(
      'weight' => -48,
      'status' => 1,
      'settings' => array(
        'allowed_html' => '<a> <em> <u> <strong> <blockquote> <ul> <ol> <li> <p> <br>',
        'filter_html_help' => 1,
        'filter_html_nofollow' => 0,
      ),
    ),
    'filter_autop' => array(
      'weight' => -46,
      'status' => 1,
      'settings' => array(),
    ),
    'filter_htmlcorrector' => array(
      'weight' => -45,
      'status' => 1,
      'settings' => array(),
    ),
  );

  filter_format_save($format);

  $settings = array(
    'default' => 1,
    'user_choose' => 0,
    'show_toggle' => 1,
    'theme' => 'advanced',
    'language' => 'da',
    'buttons' => array(
      'default' => array(
        'Bold' => 1,
        'Italic' => 1,
        'Underline' => 1,
        'BulletedList' => 1,
        'NumberedList' => 1,
        'Link' => 1,
        'Blockquote' => 1,
        'Source' => 1,
        'ShowBlocks' => 1,
      ),
      'drupal_path' => array(
        'Link' => 1,
      )
    ),
    'toolbar_loc' => 'top',
    'toolbar_align' => 'left',
    'path_loc' => 'bottom',
    'resizing' => 1,
    'verify_html' => 1,
    'preformatted' => 0,
    'convert_fonts_to_spans' => 1,
    'remove_linebreaks' => 1,
    'apply_source_formatting' => 0,
    'paste_auto_cleanup_on_paste' => 1,
    'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
    'css_setting' => 'theme',
    'css_path' => '',
    'css_classes' => '',
  );

  db_merge('wysiwyg')
    ->key(array('format' => $format->format))
    ->fields(array(
      'editor' => 'ckeditor',
      'settings' => serialize($settings),
    ))
    ->execute();
}