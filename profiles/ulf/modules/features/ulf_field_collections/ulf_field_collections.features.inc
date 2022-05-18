<?php

/**
 * @file
 * ulf_field_collections.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_field_collections_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
