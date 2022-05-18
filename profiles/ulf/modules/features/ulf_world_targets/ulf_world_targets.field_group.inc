<?php

/**
 * @file
 * ulf_world_targets.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ulf_world_targets_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_world_targets|node|course_educators|form';
  $field_group->group_name = 'group_world_targets';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course_educators';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Verdensmål',
    'weight' => '16',
    'children' => array(
      0 => 'field_world_targets',
      1 => 'field_world_targets_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Verdensmål',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-world-targets field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_world_targets|node|course_educators|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_world_targets|node|course|form';
  $field_group->group_name = 'group_world_targets';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Verdensmål',
    'weight' => '15',
    'children' => array(
      0 => 'field_world_targets',
      1 => 'field_world_targets_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Verdensmål',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-world-targets field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_world_targets|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_world_targets|node|exercise|form';
  $field_group->group_name = 'group_world_targets';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'exercise';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Verdensmål',
    'weight' => '8',
    'children' => array(
      0 => 'field_world_targets',
      1 => 'field_world_targets_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Verdensmål',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-world-targets field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_world_targets|node|exercise|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_world_targets|user|user|form';
  $field_group->group_name = 'group_world_targets';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Verdensmål',
    'weight' => '4',
    'children' => array(
      0 => 'field_world_targets',
      1 => 'field_world_targets_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Verdensmål',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-world-targets field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_world_targets|user|user|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Verdensmål');

  return $field_groups;
}
