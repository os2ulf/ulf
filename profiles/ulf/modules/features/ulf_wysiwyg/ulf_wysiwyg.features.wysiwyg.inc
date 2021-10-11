<?php

/**
 * @file
 * ulf_wysiwyg.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function ulf_wysiwyg_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: editor.
  $profiles['editor'] = array(
    'format' => 'editor',
    'editor' => 'ckeditor',
    'settings' => array(
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Undo' => 1,
          'Redo' => 1,
          'Link' => 1,
          'Superscript' => 1,
          'Subscript' => 1,
          'Source' => 1,
          'Cut' => 1,
          'Copy' => 1,
          'PasteFromWord' => 1,
          'ShowBlocks' => 1,
          'RemoveFormat' => 1,
          'Format' => 1,
        ),
        'pasteformat' => array(
          'pasteformat' => 1,
        ),
        'drupal_path' => array(
          'Link' => 1,
        ),
      ),
      'theme' => '',
      'language' => 'da',
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'acf_mode' => 0,
      'acf_allowed_content' => '',
      'css_setting' => 'theme',
      'css_theme' => 'ulf_admin',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'forcePasteAsPlainText' => 0,
      'pasteFromWordPromptCleanup' => 1,
      'pasteFromWordRemoveFontStyles' => 1,
    ),
    'preferences' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'add_to_summaries' => 1,
      'version' => '4.12.1.64749bb245',
    ),
    'name' => 'formateditor',
  );

  return $profiles;
}
