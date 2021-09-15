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
      'title_label' => t('Title'),
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
      'locked' => '1',
    ),
    'download_list' => array(
      'name' => 'Liste af downloads',
      'bundle' => 'download_list',
      'locked' => '1',
    ),
    'four_columns' => array(
      'name' => 'Fire kolonner',
      'bundle' => 'four_columns',
      'locked' => '1',
    ),
    'hero' => array(
      'name' => 'Hero',
      'bundle' => 'hero',
      'locked' => '1',
    ),
    'image_with_link' => array(
      'name' => 'Billedeblok med link',
      'bundle' => 'image_with_link',
      'locked' => '1',
    ),
    'link_list' => array(
      'name' => 'Liste af links',
      'bundle' => 'link_list',
      'locked' => '1',
    ),
    'news_list' => array(
      'name' => 'Nyhedsliste',
      'bundle' => 'news_list',
      'locked' => '1',
    ),
    'one_column' => array(
      'name' => 'En kolonne',
      'bundle' => 'one_column',
      'locked' => '1',
    ),
    'spacer' => array(
      'name' => 'Afstand',
      'bundle' => 'spacer',
      'locked' => '1',
    ),
    'text_with_image' => array(
      'name' => 'Tekst med billede',
      'bundle' => 'text_with_image',
      'locked' => '1',
    ),
    'text_with_video' => array(
      'name' => 'Tekst med video',
      'bundle' => 'text_with_video',
      'locked' => '1',
    ),
    'three_columns' => array(
      'name' => 'Tre kolonner',
      'bundle' => 'three_columns',
      'locked' => '1',
    ),
    'two_column' => array(
      'name' => 'To kolonner',
      'bundle' => 'two_column',
      'locked' => '1',
    ),
  );
  return $items;
}
