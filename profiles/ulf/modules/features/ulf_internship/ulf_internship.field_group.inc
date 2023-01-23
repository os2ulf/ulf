<?php

/**
 * @file
 * ulf_internship.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ulf_internship_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact|node|internship|form';
  $field_group->group_name = 'group_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Vis kontaktformular / Skjul kontaktformular',
    'weight' => '15',
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
  $field_groups['group_contact|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course_sub|node|internship|form';
  $field_group->group_name = 'group_course_sub';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
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
  $field_groups['group_course_sub|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course|node|internship|form';
  $field_group->group_name = 'group_course';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Forløbet',
    'weight' => '0',
    'children' => array(
      0 => 'field_full_description',
      1 => 'field_purpose',
      2 => 'title',
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
  $field_groups['group_course|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_duration|node|internship|form';
  $field_group->group_name = 'group_duration';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Varighed og pris',
    'weight' => '3',
    'children' => array(
      0 => 'field_collection_price',
      1 => 'field_duration',
      2 => 'field_duration_description',
      3 => 'field_duration_unit',
      4 => 'field_free',
      5 => 'field_price_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Varighed og pris',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-duration field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_duration|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_facilities|node|internship|form';
  $field_group->group_name = 'group_facilities';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Faciliteter',
    'weight' => '6',
    'children' => array(
      0 => 'field_facilities',
      1 => 'field_facilities_info',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Faciliteter',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'form-layout--delta',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_facilities|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_materials|node|internship|form';
  $field_group->group_name = 'group_materials';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Materialer',
    'weight' => '7',
    'children' => array(
      0 => 'field_educational_material',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Materialer',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-materials field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_materials|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|internship|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Billeder/medier',
    'weight' => '5',
    'children' => array(
      0 => 'field_image',
      1 => 'field_video',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Billeder/medier',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-media field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_media|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_placement|node|internship|form';
  $field_group->group_name = 'group_placement';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lokation',
    'weight' => '12',
    'children' => array(
      0 => 'field_map_placement',
      1 => 'field_place',
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
  $field_groups['group_placement|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_practical_information|node|internship|form';
  $field_group->group_name = 'group_practical_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Praktisk information',
    'weight' => '2',
    'children' => array(
      0 => 'field_count',
      1 => 'field_count_description',
      2 => 'field_educational_path',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Praktisk information',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'form-layout--beta',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_practical_information|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pretix|node|internship|form';
  $field_group->group_name = 'group_pretix';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'pretix',
    'weight' => '16',
    'children' => array(
      0 => 'field_pretix_date',
      1 => 'field_pretix_email_recipient',
      2 => 'field_pretix_enable',
      3 => 'field_pretix_event_url',
      4 => 'field_pretix_show_widget_from',
      5 => 'field_pretix_synchronize',
      6 => 'field_pretix_widget',
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
  $field_groups['group_pretix|node|internship|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_signup|node|internship|form';
  $field_group->group_name = 'group_signup';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'internship';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tilmelding',
    'weight' => '4',
    'children' => array(
      0 => 'field_last_signup_date',
      1 => 'field_signup_description',
      2 => 'field_signup_email',
      3 => 'field_signup_link',
      4 => 'field_signup_phone',
      5 => 'field_signup_show_link',
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
  $field_groups['group_signup|node|internship|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Aktiviteter, forberedelse og efterbehandling');
  t('Billeder/medier');
  t('Faciliteter');
  t('Forløbet');
  t('Lokation');
  t('Materialer');
  t('Praktisk information');
  t('Tilmelding');
  t('Varighed og pris');
  t('Vis kontaktformular / Skjul kontaktformular');
  t('pretix');

  return $field_groups;
}
