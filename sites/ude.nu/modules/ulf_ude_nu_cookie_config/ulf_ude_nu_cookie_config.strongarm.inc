<?php

/**
 * @file
 * ulf_ude_nu_cookie_config.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ulf_ude_nu_cookie_config_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance';
  $strongarm->value = array(
    'popup_enabled' => 0,
    'method' => 'opt_in',
    'info_template' => 'new',
    'cookie_categories' => '',
    'enable_save_preferences_button' => 1,
    'save_preferences_button_label' => 'Save preferences',
    'accept_all_categories_button_label' => 'Accept all cookies',
    'fix_first_cookie_category' => 1,
    'select_all_categories_by_default' => 0,
    'disabled_javascripts' => '',
    'whitelisted_cookies' => '',
    'consent_storage_method' => 'do_not_store',
    'popup_clicking_confirmation' => FALSE,
    'popup_info' => array(
      'value' => '<p>Vi anvender cookies for at få hjemmesiden til at fungere og at lave statistik som vi kan bruge til at forbedre hjemmesidens indhold.</p>',
      'format' => 'editor',
    ),
    'use_mobile_message' => 0,
    'mobile_popup_info' => array(
      'value' => '<h2>We use cookies on this site to enhance your user experience</h2><p>By tapping the Accept button, you agree to us doing so.</p>',
      'format' => 'plain_text',
    ),
    'mobile_breakpoint' => '768',
    'popup_agree_button_message' => 'OK, I agree',
    'show_disagree_button' => TRUE,
    'popup_disagree_button_message' => 'No, give me more info',
    'disagree_button_label' => 'No, thanks',
    'withdraw_enabled' => 0,
    'withdraw_button_on_info_popup' => 0,
    'withdraw_message' => array(
      'value' => '<h2>We use cookies on this site to enhance your user experience</h2><p>You have given your consent for us to set cookies.</p>',
      'format' => 'plain_text',
    ),
    'withdraw_tab_button_label' => 'Privacy settings',
    'withdraw_action_button_label' => 'Withdraw consent',
    'popup_agreed_enabled' => 0,
    'popup_hide_agreed' => 0,
    'popup_agreed' => array(
      'value' => '<h2>Thank you for accepting cookies</h2><p>You can now hide this message or find out more about cookies.</p>',
      'format' => 'editor',
    ),
    'popup_find_more_button_message' => 'More info',
    'popup_hide_button_message' => 'Skjul',
    'popup_link' => 'https://erhvervsstyrelsen.dk/hvad-er-cookies',
    'popup_link_new_window' => 1,
    'popup_position' => TRUE,
    'use_bare_css' => 0,
    'popup_text_hex' => 'ffffff',
    'popup_bg_hex' => '4d4d4d',
    'popup_height' => '',
    'popup_width' => '100%',
    'fixed_top_position' => 1,
    'popup_delay' => '1000',
    'disagree_do_not_show_popup' => 0,
    'reload_page' => 0,
    'popup_scrolling_confirmation' => FALSE,
    'cookie_name' => '',
    'domains_option' => '1',
    'domains_list' => '',
    'exclude_paths' => '',
    'exclude_admin_pages' => 0,
    'exclude_uid_1' => 0,
    'script_scope' => 'footer',
    'better_support_for_screen_readers' => 0,
    'cookie_session' => 0,
  );
  $export['eu_cookie_compliance'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'eu_cookie_compliance_domain';
  $strongarm->value = '';
  $export['eu_cookie_compliance_domain'] = $strongarm;

  return $export;
}
