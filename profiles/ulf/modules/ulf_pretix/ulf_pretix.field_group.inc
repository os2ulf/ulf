<?php

/**
 * @file
 * ulf_pretix.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ulf_pretix_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pretix|node|course_educators|form';
  $field_group->group_name = 'group_pretix';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course_educators';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'pretix',
    'weight' => '73',
    'children' => array(
      0 => 'field_pretix_date',
      1 => 'field_pretix_email_recipient',
      2 => 'field_pretix_synchronize',
      3 => 'field_pretix_show_widget_from',
      4 => 'field_pretix_enable',
      5 => 'field_pretix_widget',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'pretix',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-pretix field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_pretix|node|course_educators|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pretix|node|course|form';
  $field_group->group_name = 'group_pretix';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'pretix',
    'weight' => '15',
    'children' => array(
      0 => 'field_pretix_date',
      1 => 'field_pretix_email_recipient',
      2 => 'field_pretix_enable',
      3 => 'field_pretix_show_widget_from',
      4 => 'field_pretix_synchronize',
      5 => 'field_pretix_widget',
      6 => 'field_pretix_event_url',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-pretix field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_pretix|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pretix|user|user|form';
  $field_group->group_name = 'group_pretix';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'pretix',
    'weight' => '21',
    'children' => array(
      0 => 'field_pretix_api_token',
      1 => 'field_pretix_default_event_slug',
      2 => 'field_pretix_organizer_slug',
      3 => 'field_pretix_url',
      4 => 'field_pretix_email_template',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'pretix',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_pretix|user|user|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('pretix');

  return $field_groups;
}
