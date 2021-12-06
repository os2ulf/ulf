<?php

/**
 * @file
 * ulf_entityform.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ulf_entityform_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'entityform-end_user_message-field_antal_boern'.
  $field_instances['entityform-end_user_message-field_antal_boern'] = array(
    'bundle' => 'end_user_message',
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
    'field_name' => 'field_antal_boern',
    'label' => 'Antal børn',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'entityform-end_user_message-field_dato_for_besoeg'.
  $field_instances['entityform-end_user_message-field_dato_for_besoeg'] = array(
    'bundle' => 'end_user_message',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_dato_for_besoeg',
    'label' => 'Dato for besøg',
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
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'entityform-end_user_message-field_message_body'.
  $field_instances['entityform-end_user_message-field_message_body'] = array(
    'bundle' => 'end_user_message',
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'entityform-end_user_message-field_message_email'.
  $field_instances['entityform-end_user_message-field_message_email'] = array(
    'bundle' => 'end_user_message',
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
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'entityform-end_user_message-field_message_name'.
  $field_instances['entityform-end_user_message-field_message_name'] = array(
    'bundle' => 'end_user_message',
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
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'entityform-end_user_message-field_message_parent_node'.
  $field_instances['entityform-end_user_message-field_message_parent_node'] = array(
    'bundle' => 'end_user_message',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance:
  // 'entityform-end_user_message-field_skole_institution'.
  $field_instances['entityform-end_user_message-field_skole_institution'] = array(
    'bundle' => 'end_user_message',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_skole_institution',
    'label' => 'Skole/institution',
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
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Angiv din besked. 
Hvis du vil booke et forløb, så angiv venligst så mange informationer som muligt - f.eks. skole eller institution, klassetrin eller alder, antal børn, forslag til dato, dit tlf. nr. og andre informationer, der kan være gavnlige for udbyderen.');
  t('Angiv din email adresse');
  t('Angiv dit fulde navn');
  t('Antal børn');
  t('Besked');
  t('Dato for besøg');
  t('Email');
  t('Message Parent node');
  t('Navn');
  t('Skole/institution');

  return $field_instances;
}
