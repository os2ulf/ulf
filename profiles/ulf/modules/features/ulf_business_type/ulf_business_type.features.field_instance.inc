<?php

/**
 * @file
 * ulf_business_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ulf_business_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-internship-field_business_type'.
  $field_instances['node-internship-field_business_type'] = array(
    'bundle' => 'internship',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Typen af denne branche.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 37,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_business_type',
    'label' => 'Branche',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'taxonomy-index' => array(
          'status' => TRUE,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 63,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Branche');
  t('Typen af denne branche.');

  return $field_instances;
}
