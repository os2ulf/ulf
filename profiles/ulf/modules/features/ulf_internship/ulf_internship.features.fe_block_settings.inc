<?php

/**
 * @file
 * ulf_internship.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function ulf_internship_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-a2fe01e21602000aa0f97a257df409ce'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'a2fe01e21602000aa0f97a257df409ce',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ulf_admin' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ulf_admin',
        'weight' => 0,
      ),
      'ulf_hjoerring' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ulf_hjoerring',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
