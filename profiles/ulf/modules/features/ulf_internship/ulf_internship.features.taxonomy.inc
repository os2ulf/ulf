<?php

/**
 * @file
 * ulf_internship.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ulf_internship_taxonomy_default_vocabularies() {
  return array(
    'branche' => array(
      'name' => 'Branche',
      'machine_name' => 'branche',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'competencies' => array(
      'name' => 'Kompetenceområde',
      'machine_name' => 'competencies',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'interesseomraader' => array(
      'name' => 'Interesseområder',
      'machine_name' => 'interesseomraader',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'lokation' => array(
      'name' => 'Postnummer',
      'machine_name' => 'lokation',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'tilbudsforpligtelser' => array(
      'name' => 'Muligheder',
      'machine_name' => 'tilbudsforpligtelser',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
