<?php

/**
 * @file
 * ulf_pagebuilder.captcha.inc
 */

/**
 * Implements hook_captcha_default_points().
 */
function ulf_pagebuilder_captcha_default_points() {
  $export = array();

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'kontaktformular_entityform_edit_form';
  $captcha->module = '';
  $captcha->captcha_type = '';
  $export['kontaktformular_entityform_edit_form'] = $captcha;

  return $export;
}
