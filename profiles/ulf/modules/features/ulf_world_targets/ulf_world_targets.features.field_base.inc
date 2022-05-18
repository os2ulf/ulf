<?php

/**
 * @file
 * ulf_world_targets.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ulf_world_targets_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_world_targets'.
  $field_bases['field_world_targets'] = array(
    'active' => 1,
    'cardinality' => 4,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_world_targets',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => '1. Afskaf fattigdom',
        2 => '2. Stop sult',
        3 => '3. Sundhed og trivsel',
        4 => '4. Kvalitetsuddannelse',
        5 => '5. Ligestilling mellem kønnene',
        6 => '6. Rent vand og sanitet',
        7 => '7. Bæredygtig energi',
        8 => '8. Anstændige jobs og økonomisk vækst',
        9 => '9. Industri, innovation og infrastruktur',
        10 => '10. Mindre ulighed',
        11 => '11. Bæredygtige byer og lokalsamfund',
        12 => '12. Ansvarligt forbrug og produktion',
        13 => '13. Klimaindsats',
        14 => '14. Livet i havet',
        15 => '15. Livet på land',
        16 => '16. Fred, retfærdighed og stærke institutioner',
        17 => '17. Partnerskaber for forhandling',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_world_targets_description'.
  $field_bases['field_world_targets_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_world_targets_description',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
