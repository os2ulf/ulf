<?php

/**
 * @file
 * ulf_internship.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ulf_internship_user_default_roles() {
  $roles = array();

  // Exported role: company.
  $roles['company'] = array(
    'name' => 'company',
    'weight' => 6,
  );

  // Exported role: company consultant.
  $roles['company consultant'] = array(
    'name' => 'company consultant',
    'weight' => 5,
  );

  return $roles;
}
