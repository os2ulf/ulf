<?php

/**
 * @file
 * ulf_business_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_business_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
