<?php

/**
 * @file
 * ulf_pagebuilder.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_pagebuilder_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_entityform_type().
 */
function ulf_pagebuilder_default_entityform_type() {
  $items = array();
  $items['kontaktformular'] = entity_import('entityform_type', '{
    "type" : "kontaktformular",
    "label" : "Kontaktformular",
    "data" : {
      "draftable" : 0,
      "draft_redirect_path" : "",
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "email" },
      "submit_button_text" : "",
      "submit_confirm_msg" : "",
      "your_submissions" : "",
      "disallow_resubmit_msg" : "",
      "delete_confirm_msg" : "",
      "page_title_view" : "",
      "preview_page" : 0,
      "submission_page_title" : "Tak for din henvendelse",
      "submission_text" : {
        "value" : "Tak for din henvendelse, du h\\u00f8rer fra os hurtigst muligt.",
        "format" : "email"
      },
      "submission_show_submitted" : 0,
      "submissions_view" : "default",
      "user_submissions_view" : "default",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "1" : "1", "2" : "2", "3" : 0, "4" : 0, "5" : 0, "6" : 0, "7" : 0 },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : { "value" : "", "format" : "email" },
      "course_contact_form" : { "is_course_contact_form" : 0, "providers" : [] }
    },
    "weight" : "0",
    "paths" : []
  }');
  return $items;
}

/**
 * Implements hook_image_default_styles().
 */
function ulf_pagebuilder_image_default_styles() {
  $styles = array();

  // Exported image style: hero.
  $styles['hero'] = array(
    'label' => 'Hero',
    'effects' => array(
      1 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => '',
          'height' => 800,
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'hero',
          '#imageinfo_cache_effect_callback' => 'manualcrop_crop_effect',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: pagebuilder.
  $styles['pagebuilder'] = array(
    'label' => 'Pagebuilder',
    'effects' => array(
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 984,
          'height' => '',
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: pagebuilder_image.
  $styles['pagebuilder_image'] = array(
    'label' => 'Pagebuilder billede',
    'effects' => array(
      4 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 984,
          'height' => 654,
          'keepproportions' => 1,
          'reuse_crop_style' => '',
          'style_name' => 'pagebuilder_image',
          '#imageinfo_cache_effect_callback' => 'manualcrop_crop_effect',
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ulf_pagebuilder_node_info() {
  $items = array(
    'page_with_blocks' => array(
      'name' => t('Statisk side med blokke'),
      'base' => 'node_content',
      'description' => t('Statisk side med pagebuilder funktionalitet'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function ulf_pagebuilder_paragraphs_info() {
  $items = array(
    'appetizer' => array(
      'name' => 'Appetitvækker',
      'bundle' => 'appetizer',
      'label' => 'Appetitvækker',
      'description' => '',
      'locked' => '1',
    ),
    'download_list' => array(
      'name' => 'Liste af downloads',
      'bundle' => 'download_list',
      'label' => 'Liste af downloads',
      'description' => '',
      'locked' => '1',
    ),
    'four_columns' => array(
      'name' => 'Fire kolonner',
      'bundle' => 'four_columns',
      'label' => 'Fire kolonner',
      'description' => '',
      'locked' => '1',
    ),
    'hero' => array(
      'name' => 'Hero',
      'bundle' => 'hero',
      'label' => 'Hero',
      'description' => '',
      'locked' => '1',
    ),
    'image_with_link' => array(
      'name' => 'Billedeblok med link',
      'bundle' => 'image_with_link',
      'label' => 'Billedeblok med link',
      'description' => '',
      'locked' => '1',
    ),
    'kontakt_formular' => array(
      'name' => 'Kontakt formular',
      'bundle' => 'kontakt_formular',
      'label' => 'Kontakt formular',
      'description' => '',
      'locked' => '1',
    ),
    'link_list' => array(
      'name' => 'Liste af links',
      'bundle' => 'link_list',
      'label' => 'Liste af links',
      'description' => '',
      'locked' => '1',
    ),
    'news_list' => array(
      'name' => 'Nyhedsliste',
      'bundle' => 'news_list',
      'label' => 'Nyhedsliste',
      'description' => '',
      'locked' => '1',
    ),
    'one_column' => array(
      'name' => 'En kolonne',
      'bundle' => 'one_column',
      'label' => 'En kolonne',
      'description' => '',
      'locked' => '1',
    ),
    'spacer' => array(
      'name' => 'Afstand',
      'bundle' => 'spacer',
      'label' => 'Afstand',
      'description' => '',
      'locked' => '1',
    ),
    'text_with_image' => array(
      'name' => 'Tekst med billede',
      'bundle' => 'text_with_image',
      'label' => 'Tekst med billede',
      'description' => '',
      'locked' => '1',
    ),
    'text_with_video' => array(
      'name' => 'Tekst med video',
      'bundle' => 'text_with_video',
      'label' => 'Tekst med video',
      'description' => '',
      'locked' => '1',
    ),
    'three_columns' => array(
      'name' => 'Tre kolonner',
      'bundle' => 'three_columns',
      'label' => 'Tre kolonner',
      'description' => '',
      'locked' => '1',
    ),
    'two_column' => array(
      'name' => 'To kolonner',
      'bundle' => 'two_column',
      'label' => 'To kolonner',
      'description' => '',
      'locked' => '1',
    ),
  );
  return $items;
}
