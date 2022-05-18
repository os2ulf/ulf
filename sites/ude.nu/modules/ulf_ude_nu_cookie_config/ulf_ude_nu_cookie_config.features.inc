<?php

/**
 * @file
 * ulf_ude_nu_cookie_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_ude_nu_cookie_config_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
