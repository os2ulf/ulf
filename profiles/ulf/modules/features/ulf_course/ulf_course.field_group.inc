<?php

/**
 * @file
 * ulf_course.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ulf_course_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact|node|course|form';
  $field_group->group_name = 'group_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Vis kontaktformular / Skjul kontaktformular',
    'weight' => '13',
    'children' => array(
      0 => 'field_message_form',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Vis kontaktformular / Skjul kontaktformular',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-contact field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_contact|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course_sub|node|course|form';
  $field_group->group_name = 'group_course_sub';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Aktiviteter, forberedelse og efterbehandling',
    'weight' => '1',
    'children' => array(
      0 => 'field_activities',
      1 => 'field_background_knowledge',
      2 => 'field_post_work',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Aktiviteter, forberedelse og efterbehandling',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'form-layout--epsilon',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_course_sub|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course|node|course|form';
  $field_group->group_name = 'group_course';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Forløbet',
    'weight' => '0',
    'children' => array(
      0 => 'field_full_description',
      1 => 'field_purpose',
      2 => 'field_target_group',
      3 => 'field_banner',
      4 => 'title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Forløbet',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => 'node_course_form_group_course',
        'classes' => 'form-layout--alfa',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_course|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_duration|node|course|form';
  $field_group->group_name = 'group_duration';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Varighed og pris',
    'weight' => '3',
    'children' => array(
      0 => 'field_collection_price',
      1 => 'field_duration_unit',
      2 => 'field_free',
      3 => 'field_duration',
      4 => 'field_duration_description',
      5 => 'field_price_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Varighed og pris',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-duration field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_duration|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_facilities|node|course|form';
  $field_group->group_name = 'group_facilities';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Faciliteter',
    'weight' => '7',
    'children' => array(
      0 => 'field_facilities',
      1 => 'field_facilities_info',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Faciliteter',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'form-layout--delta',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_facilities|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_materials|node|course|form';
  $field_group->group_name = 'group_materials';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Materialer',
    'weight' => '8',
    'children' => array(
      0 => 'field_educational_material',
      1 => 'field_inspirational_material',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Materialer',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-materials field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_materials|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|course|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Billeder/medier',
    'weight' => '6',
    'children' => array(
      0 => 'field_image',
      1 => 'field_video',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Billeder/medier',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-media field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_media|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_period|node|course|form';
  $field_group->group_name = 'group_period';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Periode',
    'weight' => '5',
    'children' => array(
      0 => 'field_period',
      1 => 'field_period_full_year',
      2 => 'field_period_info',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Periode',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'form-layout--gamma',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_period|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_placement|node|course|form';
  $field_group->group_name = 'group_placement';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lokation',
    'weight' => '11',
    'children' => array(
      0 => 'field_place',
      1 => 'field_map_placement',
      2 => 'locations',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-placement field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_placement|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_practical_information|node|course|form';
  $field_group->group_name = 'group_practical_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Praktisk information',
    'weight' => '2',
    'children' => array(
      0 => 'field_count',
      1 => 'field_educational_goals',
      2 => 'field_offer_type',
      3 => 'field_subject',
      4 => 'field_subjects_primary_school',
      5 => 'field_subjects_youth',
      6 => 'field_target_group_sub',
      7 => 'field_count_description',
      8 => 'field_practical_info_buttons',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Praktisk information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'form-layout--beta',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_practical_information|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_signup|node|course|form';
  $field_group->group_name = 'group_signup';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tilmelding',
    'weight' => '4',
    'children' => array(
      0 => 'field_last_signup_date',
      1 => 'field_signup_email',
      2 => 'field_signup_link',
      3 => 'field_signup_description',
      4 => 'field_signup_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Tilmelding',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-signup field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_signup|node|course|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Aktiviteter, forberedelse og efterbehandling');
  t('Billeder/medier');
  t('Faciliteter');
  t('Forløbet');
  t('Lokation');
  t('Materialer');
  t('Periode');
  t('Praktisk information');
  t('Tilmelding');
  t('Varighed og pris');
  t('Vis kontaktformular / Skjul kontaktformular');

  return $field_groups;
}
