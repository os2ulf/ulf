<?php

/*
 * Contains alter hooks to implement extra functionality, if ulf_entityform_enable_editor_forms is set to true
 */

/**
 * Implements hook_secure_permissions().
 */
function ulf_entityform_secure_permissions($role) {
  $permissions = [];

  if($role == 'editor') {
    $permissions = [
      'administer entityform types',
      'view any entityform',
      'edit any entityform',
      'delete any entityform',
      'administer fields',
      'administer field permissions',
      'access private fields',
    ];
  }

  return $permissions;
}

/**
 * Implements hook_form_alter().
 */
function _ulf_entityform_form_alter(&$form, &$form_state, $form_id) {
  if($form_id == 'entityform_type_overview_form') {
    foreach ($form['table']['#rows'] as $key => $row) {
      if(isset($row[0]['data'])) {
        if(isset($row[0]['data']['#name']) && $row[0]['data']['#name'] == 'basisform') {
          unset($form['table']['#rows'][$key]);
        }
      }
    }
  }

  $form_ids = [
    'course_node_form',
    'course_educators_node_form',
    'internship_node_form',
    'education_node_form'
  ];
  if(in_array($form_id, $form_ids)) {

    $node = $form_state['node'];

    $available_form_types = [];
    foreach (entityform_get_types() as $entityform_type) {
      if(isset($entityform_type->data['course_contact_form']['is_course_contact_form']) && $entityform_type->data['course_contact_form']['is_course_contact_form'] == 1) {
        if(isset($entityform_type->data['course_contact_form']['providers'])) {
          $providers = array_filter($entityform_type->data['course_contact_form']['providers']);
        } else {
          $providers = true;
        }
        $available_form_types[$entityform_type->id] = $providers ? $providers : true;
      }
    }

    $form['author']['name']['#ajax'] = [
      'callback' => 'dynamically_change_field_message_form_options',
      'wrapper' => 'field-message-form-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ];

    $form['field_message_form'][LANGUAGE_NONE]['#prefix'] = '<div id="field-message-form-wrapper">';
    $form['field_message_form'][LANGUAGE_NONE]['#suffix'] = '</div>';

    if(isset($form_state['values'])) {
      //ajax request
      $user = user_load_by_name($form_state['values']['name']);
      if($user) {
        $provider = $user->uid;
      } else {
        $provider = 0;
      }
    } else {
      $provider = $node->uid;
    }
    $message_form_options = $form['field_message_form'][LANGUAGE_NONE]['#options'];
    foreach ($message_form_options as $key => $value) {
      if($key == '_none') {
        continue;
      }
      if(isset($available_form_types[$key])) {
        if(is_array($available_form_types[$key]) && !in_array($provider, $available_form_types[$key])) {
          unset($message_form_options[$key]);
        }
      } else {
        unset($message_form_options[$key]);
      }
    }

    $form['field_message_form'][LANGUAGE_NONE]['#options'] = $message_form_options;
    if(count($message_form_options) <= 1) {
      $form['field_message_form'][LANGUAGE_NONE]['#description'] = t('No available forms for this provider');
    }
  }
}
function dynamically_change_field_message_form_options($form, $form_state) {
  return $form['field_message_form'];
}
/**
 * Implements hook_form_FORM_ID_alter().
 */
function ulf_entityform_form_entityform_type_form_alter(&$form, &$form_state) {
  $entityform_type = $form['#entityform_type'];

  $form['data']['course_contact_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Course contact form'),
    '#collapsible' => TRUE,
    '#weight' => 20,
  );
  $form['data']['course_contact_form']['is_course_contact_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('This form can be used as a course contact form'),
    '#default_value' => empty($entityform_type->data['course_contact_form']['is_course_contact_form']) ? 0 : $entityform_type->data['course_contact_form']['is_course_contact_form'],
  );

  $query = db_select('users', 'u');
  $query->fields('u', ['uid']);
  $query->fields('n', ['field_profile_name_value']);
  $query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');
  $query->leftJoin('role', 'r', 'ur.rid = r.rid');
  $query->leftJoin('field_data_field_profile_name', 'n', 'u.uid = n.entity_id');
  $query->condition('r.name', ['company', 'course provider'], 'IN');
  $query->condition('n.entity_type', 'user', '=');
  $result = $query->execute()->fetchAllKeyed(0, 1);

  $form['data']['course_contact_form']['providers'] = array(
    '#type' => 'select',
    '#title' => t('Only available to specific providers'),
    '#multiple' => true,
    '#options' => $result,
    '#default_value' => empty($entityform_type->data['course_contact_form']['providers']) ? [] : $entityform_type->data['course_contact_form']['providers'],
    '#description' => t('If none is selected, it will be available to all providers'),
    '#states' => [
      'invisible' => [
        ':input[name="data[course_contact_form][is_course_contact_form]"]' => ['checked' => false],
      ],
    ],
  );
  $form['data']['course_contact_form']['info'] = [
    '#type' => 'container',
    'content' => [
      '#markup' => '
        <h3>Information about form message notifications</h3>
        <p>You have the following options automatically integrated:</p>
        <ul>
        <li><b>Automatic recipient based on the course provider of the current page:</b> You have to add the form field "field_message_parent_node" to the form, in order to have the message automatically sent to the course provider</li>
        <li><b>You choose a specific provider:</b> You have to add the form fields "field_message_recipient_provider" and "field_message_parent_node_nomail" to the form, in order to have the message automatically sent to your chosen provider</li>
        <li><b>You submit a specific email address:</b> You have to add the form fields "field_message_recipient_mail" and "field_message_parent_node_nomail" to the form, in order to have the message automatically sent to your submitted email address</li>
        </ul>
        <p>Be aware, that if none of the above criteria have been met, no notification will be sent, unless you set it up yourself</p>
      ',
    ],
    '#states' => [
      'invisible' => [
        ':input[name="data[course_contact_form][is_course_contact_form]"]' => ['checked' => false],
      ],
    ],
  ];
}

function ulf_entityform_default_entityform_type_alter(&$entityform_types) {
  if(isset($entityform_types['end_user_message'])) {
    $entityform_types['end_user_message']->data['course_contact_form']['is_course_contact_form'] = 1;
    $entityform_types['basisform'] = entity_import('entityform_type', '{
      "type" : "basisform",
      "label" : "Basisform",
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
          "value" : "\\u003Cp\\u003EDin besked er sendt videre til udbyderen.\\u003C\\/p\\u003E\\u003Cp\\u003E---\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cstrong\\u003EAfsender:\\u003C\\/strong\\u003E [entityform:field-message-name]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cstrong\\u003EAfsender email:\\u003C\\/strong\\u003E [entityform:field-message-email]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cstrong\\u003EBesked:\\u003C\\/strong\\u003E\\u003Cbr\\u003E[entityform:field-message-body]\\u003C\\/p\\u003E\\u003Cp\\u003E---\\u003C\\/p\\u003E\\u003Cp\\u003EMed venlig hilsen\\u003Cbr \\/\\u003E[site:name]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Ca class=\\u0022button\\u0022 href=\\u0022javascript:history.back()\\u0022\\u003ETilbage\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html"
        },
        "submission_show_submitted" : 0,
        "submissions_view" : "default",
        "user_submissions_view" : "default",
        "form_status" : "ENTITYFORM_OPEN",
        "roles" : { "1" : "1", "2" : "2", "3" : 0, "4" : 0, "5" : 0, "6" : 0, "7" : 0 },
        "resubmit_action" : "new",
        "redirect_path" : "",
        "instruction_pre" : { "value" : "", "format" : "plain_text" },
        "course_contact_form" : { "is_course_contact_form" : 0, "providers" : [] }
      },
      "weight" : "0",
      "paths" : []
    }');
  }
}

/**
 * Implements hook_system_info_alter().
 */
function ulf_entityform_system_info_alter(&$info, $file, $type) {
  if($file->name == 'ulf_field_bases') {
    $info['features']['field_base'][] = 'field_message_parent_node_nomail';
    $info['features']['field_base'][] = 'field_message_recipient_mail';
    $info['features']['field_base'][] = 'field_message_recipient_provider';
  }

  if($file->name == 'ulf_entityform') {
    $info['features']['entityform_type'][] = 'basisform';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_body';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_email';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_name';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_parent_node';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_parent_node_nomail';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_recipient_mail';
    $info['features']['field_instance'][] = 'entityform-basisform-field_message_recipient_provider';
    $info['features']['rules_config'][] = 'ulf_entityform_send_email_on_end_user_message_email';
    $info['features']['rules_config'][] = 'ulf_entityform_send_email_on_end_user_message_provider';
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function ulf_entityform_field_default_field_instances_alter(&$fields) {
  // Exported field_instance: 'entityform-basisform-field_message_body'.
  $fields['entityform-basisform-field_message_body'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Angiv din besked.
Hvis du vil booke et forløb, så angiv venligst så mange informationer som muligt - f.eks. skole eller institution, klassetrin eller alder, antal børn, forslag til dato, dit tlf. nr. og andre informationer, der kan være gavnlige for udbyderen.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_body',
    'label' => 'Besked',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 500,
        'maxlength_js_enforce' => 0,
        'maxlength_js_label' => '<strong>@remaining</strong>/@limit',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 33,
    ),
  );
  // Exported field_instance: 'entityform-basisform-field_message_email'.
  $fields['entityform-basisform-field_message_email'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Angiv din email adresse',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_email',
    'label' => 'Email',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'emailwidget',
      'weight' => 32,
    ),
  );
  // Exported field_instance: 'entityform-basisform-field_message_name'.
  $fields['entityform-basisform-field_message_name'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Angiv dit fulde navn',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_name',
    'label' => 'Navn',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
  );

  // Exported field_instance: 'entityform-basisform-field_message_parent_node'.
  $fields['entityform-basisform-field_message_parent_node'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_parent_node',
    'label' => 'Message Parent node',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 34,
    ),
  );


  // Exported field_instance:
  // 'entityform-basisform-field_message_parent_node_nomail'.
  $fields['entityform-basisform-field_message_parent_node_nomail'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_parent_node_nomail',
    'label' => 'Message parent node nomail',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 35,
    ),
  );

  // Exported field_instance: 'entityform-basisform-field_message_recipient_mail'.
  $fields['entityform-basisform-field_message_recipient_mail'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_recipient_mail',
    'label' => 'Message recipient mail',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'html5_tools',
      'settings' => array(),
      'type' => 'emailwidget',
      'weight' => 37,
    ),
  );

  // Exported field_instance:
  // 'entityform-basisform-field_message_recipient_provider'.
  $fields['entityform-basisform-field_message_recipient_provider'] = array(
    'bundle' => 'basisform',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_message_recipient_provider',
    'label' => 'Message recipient provider',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 36,
    ),
  );
}
/**
 * Implements hook_field_default_field_bases_alter().
 */
function ulf_entityform_field_default_field_bases_alter(&$fields) {
//  if(isset($fields['field_message_parent_node'])) {

    // Exported field_base: 'field_message_parent_node_nomail'.
    $fields['field_message_parent_node_nomail'] = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_message_parent_node_nomail',
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 0,
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'type' => 'none',
          ),
          'target_bundles' => array(),
        ),
        'target_type' => 'node',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
    );

    // Exported field_base: 'field_message_recipient_mail'.
    $fields['field_message_recipient_mail'] = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_message_recipient_mail',
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(
        'max_length' => 255,
      ),
      'translatable' => 0,
      'type' => 'text',
    );

    // Exported field_base: 'field_message_recipient_provider'.
    $fields['field_message_recipient_provider'] = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_message_recipient_provider',
      'indexes' => array(
        'target_id' => array(
          0 => 'target_id',
        ),
      ),
      'locked' => 0,
      'module' => 'entityreference',
      'settings' => array(
        'handler' => 'base',
        'handler_settings' => array(
          'behaviors' => array(
            'views-select-list' => array(
              'status' => 0,
            ),
          ),
          'sort' => array(
            'direction' => 'ASC',
            'property' => 'name',
            'type' => 'property',
          ),
          'target_bundles' => array(),
        ),
        'target_type' => 'user',
      ),
      'translatable' => 0,
      'type' => 'entityreference',
    );
//  }
}

/**
 * Implements hook_default_rules_configuration_alter().
 */
function ulf_entityform_default_rules_configuration_alter(&$configs) {
  if(isset($configs['rules_send_email_on_end_user_message'])) {

    $configs['ulf_entityform_send_email_on_end_user_message_email'] = entity_import('rules_config', '{ "ulf_entityform_send_email_on_end_user_message_email" : {
        "LABEL" : "Send email on end user message to specific email address",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "TAGS" : [ "Message" ],
        "REQUIRES" : [ "rules", "mimemail", "entityform" ],
        "ON" : { "entityform_insert" : [] },
        "IF" : [
          { "entity_has_field" : { "entity" : [ "entityform" ], "field" : "field_message_recipient_mail" } },
          { "entity_has_field" : {
              "entity" : [ "entityform" ],
              "field" : "field_message_parent_node_nomail"
            }
          }
        ],
        "DO" : [
          { "entity_fetch" : {
              "USING" : {
                "type" : "node",
                "id" : [ "entityform:field-message-parent-node-nomail:nid" ]
              },
              "PROVIDE" : { "entity_fetched" : { "parent_node" : "Parent node" } }
            }
          },
          { "mimemail" : {
              "USING" : {
                "key" : "Send email on end user message",
                "to" : "[entityform:field-message-recipient-mail]",
                "from_name" : "[entityform:field-message-name]",
                "from_mail" : "[site:mail]",
                "reply_to" : "[entityform:field-message-email]",
                "subject" : "Henvendelse ang. [parent-node:title] fra [entityform:field-message-name]",
                "body" : "Henvendelse ang. [parent-node:title] ([parent-node:url]) fra [entityform:field-message-name]\\r\\n\\r\\n---\\r\\n\\u003Cstrong\\u003EFra:\\u003C\\/strong\\u003E [entityform:field-message-name]\\r\\n\\u003Cstrong\\u003EEmail:\\u003C\\/strong\\u003E [entityform:field-message-email]\\r\\n\\u003Cstrong\\u003E[parent-node:title]\\u003C\\/strong\\u003E\\r\\n\\u003Cstrong\\u003EBesked:\\u003C\\/strong\\u003E\\r\\n[entityform:field-message-body]\\r\\n\\r\\n---\\r\\n\\r\\nMed venlig hilsen\\r\\n[site:name]",
                "language" : [ "" ]
              },
              "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
            }
          }
        ]
      }
    }');
    $configs['ulf_entityform_send_email_on_end_user_message_provider'] = entity_import('rules_config', '{ "ulf_entityform_send_email_on_end_user_message_provider" : {
        "LABEL" : "Send email on end user message to specific provider",
        "PLUGIN" : "reaction rule",
        "OWNER" : "rules",
        "TAGS" : [ "Message" ],
        "REQUIRES" : [ "rules", "mimemail", "entityform" ],
        "ON" : { "entityform_insert" : [] },
        "IF" : [
          { "entity_has_field" : {
              "entity" : [ "entityform" ],
              "field" : "field_message_recipient_provider"
            }
          },
          { "entity_has_field" : {
              "entity" : [ "entityform" ],
              "field" : "field_message_parent_node_nomail"
            }
          }
        ],
        "DO" : [
          { "entity_fetch" : {
              "USING" : {
                "type" : "user",
                "id" : [ "entityform:field-message-recipient-provider:uid" ]
              },
              "PROVIDE" : { "entity_fetched" : { "message_recipient_provider" : "Message recipient provider" } }
            }
          },
          { "entity_fetch" : {
              "USING" : {
                "type" : "node",
                "id" : [ "entityform:field-message-parent-node-nomail:nid" ]
              },
              "PROVIDE" : { "entity_fetched" : { "parent_node" : "Parent node" } }
            }
          },
          { "mimemail" : {
              "USING" : {
                "key" : "Send email on end user message",
                "to" : "[message-recipient-provider:field-profile-mail]",
                "from_name" : "[entityform:field-message-name]",
                "from_mail" : "[site:mail]",
                "reply_to" : "[entityform:field-message-email]",
                "subject" : "Henvendelse ang. [parent-node:title] fra [entityform:field-message-name]",
                "body" : "Henvendelse ang. [parent-node:title] ([parent-node:url]) fra [entityform:field-message-name]\\r\\n\\r\\n---\\r\\n\\u003Cstrong\\u003EFra:\\u003C\\/strong\\u003E [entityform:field-message-name]\\r\\n\\u003Cstrong\\u003EEmail:\\u003C\\/strong\\u003E [entityform:field-message-email]\\r\\n\\u003Cstrong\\u003E[parent-node:title]\\u003C\\/strong\\u003E\\r\\n\\u003Cstrong\\u003EBesked:\\u003C\\/strong\\u003E\\r\\n[entityform:field-message-body]\\r\\n\\r\\n---\\r\\n\\r\\nMed venlig hilsen\\r\\n[site:name]",
                "language" : [ "" ]
              },
              "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
            }
          }
        ]
      }
    }');
  }
}
