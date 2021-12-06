<?php

/**
 * @file
 * ulf_entityform.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_entityform_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_entityform_type().
 */
function ulf_entityform_default_entityform_type() {
  $items = array();
  $items['end_user_message'] = entity_import('entityform_type', '{
    "type" : "end_user_message",
    "label" : "Vis kontaktformular til udbyder",
    "data" : {
      "draftable" : 0,
      "draft_redirect_path" : "",
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "editor" },
      "submit_button_text" : "",
      "submit_confirm_msg" : "",
      "your_submissions" : "",
      "disallow_resubmit_msg" : "",
      "delete_confirm_msg" : "",
      "page_title_view" : "",
      "preview_page" : 0,
      "submission_page_title" : "Beskeden er sendt videre",
      "submission_text" : {
        "value" : "\\u003Cp\\u003EDin besked er sendt videre til udbyderen.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E---\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Cstrong\\u003EAfsender:\\u003C\\/strong\\u003E [entityform:field-message-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Cstrong\\u003EAfsender email:\\u003C\\/strong\\u003E [entityform:field-message-email]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\r\\n\\u003Cstrong\\u003ESkole\\/institution:\\u003C\\/strong\\u003E [entityform:field-skole-institution]\\u003Cbr \\/\\u003E\\r\\n\\u003Cstrong\\u003EDato for bes\\u00f8g:\\u003C\\/strong\\u003E [entityform:field-dato-for-besoeg]\\u003Cbr \\/\\u003E\\r\\n\\u003Cstrong\\u003EAntal b\\u00f8rn:\\u003C\\/strong\\u003E [entityform:field-antal-boern]\\r\\n\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Cstrong\\u003EBesked:\\u003C\\/strong\\u003E\\u003Cbr\\u003E[entityform:field-message-body]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E---\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003Cbr \\/\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Ca class=\\u0022button\\u0022 href=\\u0022javascript:history.back()\\u0022\\u003ETilbage\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
        "format" : "full_html"
      },
      "submission_show_submitted" : 0,
      "submissions_view" : "default",
      "user_submissions_view" : "default",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "1" : "1", "2" : "2", "3" : 0, "4" : 0, "5" : 0 },
      "resubmit_action" : "new",
      "redirect_path" : "",
      "instruction_pre" : { "value" : "", "format" : "plain_text" }
    },
    "weight" : "0",
    "paths" : []
  }');
  return $items;
}
