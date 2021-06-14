<?php

/**
 * @file
 * ulf_business_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ulf_business_type_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_business_type|node|internship|form';
  $field_group->group_name = 'group_business_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Branche',
    'weight' => '10',
    'children' => array(
      0 => 'field_business_type',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-business-type field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_business_type|node|internship|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Branche');

  return $field_groups;
}
