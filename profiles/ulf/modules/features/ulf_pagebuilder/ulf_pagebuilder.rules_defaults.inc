<?php

/**
 * @file
 * ulf_pagebuilder.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ulf_pagebuilder_default_rules_configuration() {
  $items = array();
  $items['ulf_entityform_send_email_on_contact_form_message'] = entity_import('rules_config', '{ "ulf_entityform_send_email_on_contact_form_message" : {
      "LABEL" : "Send email on contact form message",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Message" ],
      "REQUIRES" : [ "rules", "mimemail", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "entityform" ], "field" : "field_contact_form_recipient" } }
      ],
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "Send email on contact form message",
              "to" : "[entityform:field-contact-form-recipient]",
              "from_name" : "[entityform:field-contact-form-name]",
              "from_mail" : "[site:mail]",
              "reply_to" : "[entityform:field-contact-form-email]",
              "subject" : "Henvendelse fra kontakt formular p\\u00e5 [site:name].",
              "body" : "Henvendelse fra kontakt formular p\\u00e5 [site:name].\\r\\n\\r\\n---\\r\\n\\u003Cstrong\\u003EFra:\\u003C\\/strong\\u003E [entityform:field-contact-form-name]\\r\\n\\u003Cstrong\\u003EEmail:\\u003C\\/strong\\u003E [entityform:field-contact-form-email]\\r\\n\\r\\n\\u003Cstrong\\u003EBesked:\\u003C\\/strong\\u003E\\r\\n[entityform:field-contact-form-message]\\r\\n\\r\\n---\\r\\n\\r\\nMed venlig hilsen\\r\\n[site:name]",
              "language" : [ "site:current-page:language" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  return $items;
}
