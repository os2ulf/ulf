<?php

/**
 * @file
 * ulf_business_type.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ulf_business_type_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_business_type'.
  $field_bases['field_business_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_business_type',
    'field_permissions' => array(
      'type' => 0,
    ),
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
      'target_type' => 'taxonomy_vocabulary',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
