<?php

/**
 * @file
 * ulf_internship.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ulf_internship_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'company consultant' => 'company consultant',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access broken links report'.
  $permissions['access broken links report'] = array(
    'name' => 'access broken links report',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'linkchecker',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access own broken links report'.
  $permissions['access own broken links report'] = array(
    'name' => 'access own broken links report',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'linkchecker',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access toolbar'.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: 'access workbench'.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'workbench',
  );

  // Exported permission: 'add better descriptions to fields'.
  $permissions['add better descriptions to fields'] = array(
    'name' => 'add better descriptions to fields',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'better_field_descriptions',
  );

  // Exported permission: 'administer EU Cookie Compliance popup'.
  $permissions['administer EU Cookie Compliance popup'] = array(
    'name' => 'administer EU Cookie Compliance popup',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'eu_cookie_compliance',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer custom content'.
  $permissions['administer custom content'] = array(
    'name' => 'administer custom content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'ctools_custom_content',
  );

  // Exported permission: 'administer custom settings'.
  $permissions['administer custom settings'] = array(
    'name' => 'administer custom settings',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'ulf_admin_panel',
  );

  // Exported permission: 'administer entityform types'.
  $permissions['administer entityform types'] = array(
    'name' => 'administer entityform types',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'administer field permissions'.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'administer fields'.
  $permissions['administer fields'] = array(
    'name' => 'administer fields',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'field',
  );

  // Exported permission: 'administer mail templates'.
  $permissions['administer mail templates'] = array(
    'name' => 'administer mail templates',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'mail_edit',
  );

  // Exported permission: 'administer mailchimp'.
  $permissions['administer mailchimp'] = array(
    'name' => 'administer mailchimp',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'mailchimp',
  );

  // Exported permission: 'administer mailchimp signup entities'.
  $permissions['administer mailchimp signup entities'] = array(
    'name' => 'administer mailchimp signup entities',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'mailchimp_signup',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer nodequeue'.
  $permissions['administer nodequeue'] = array(
    'name' => 'administer nodequeue',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer path metatags'.
  $permissions['administer path metatags'] = array(
    'name' => 'administer path metatags',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'path_metatags_ui',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer ulf pretix settings'.
  $permissions['administer ulf pretix settings'] = array(
    'name' => 'administer ulf pretix settings',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'ulf_pretix',
  );

  // Exported permission: 'administer ulf pretix user settings'.
  $permissions['administer ulf pretix user settings'] = array(
    'name' => 'administer ulf pretix user settings',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'ulf_pretix',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer user locations'.
  $permissions['administer user locations'] = array(
    'name' => 'administer user locations',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'location_user',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer workbench moderation'.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'assign company consultant role'.
  $permissions['assign company consultant role'] = array(
    'name' => 'assign company consultant role',
    'roles' => array(
      'company consultant' => 'company consultant',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign company role'.
  $permissions['assign company role'] = array(
    'name' => 'assign company role',
    'roles' => array(
      'company consultant' => 'company consultant',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass workbench moderation'.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'user',
  );

  // Exported permission: 'clone node'.
  $permissions['clone node'] = array(
    'name' => 'clone node',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'create html_block content'.
  $permissions['create html_block content'] = array(
    'name' => 'create html_block content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create internship content'.
  $permissions['create internship content'] = array(
    'name' => 'create internship content',
    'roles' => array(
      'company consultant' => 'company consultant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create news content'.
  $permissions['create news content'] = array(
    'name' => 'create news content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create static_page content'.
  $permissions['create static_page content'] = array(
    'name' => 'create static_page content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'path',
  );

  // Exported permission: 'delete any entityform'.
  $permissions['delete any entityform'] = array(
    'name' => 'delete any entityform',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'delete any html_block content'.
  $permissions['delete any html_block content'] = array(
    'name' => 'delete any html_block content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any news content'.
  $permissions['delete any news content'] = array(
    'name' => 'delete any news content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any static_page content'.
  $permissions['delete any static_page content'] = array(
    'name' => 'delete any static_page content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own html_block content'.
  $permissions['delete own html_block content'] = array(
    'name' => 'delete own html_block content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own news content'.
  $permissions['delete own news content'] = array(
    'name' => 'delete own news content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own static_page content'.
  $permissions['delete own static_page content'] = array(
    'name' => 'delete own static_page content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any entityform'.
  $permissions['edit any entityform'] = array(
    'name' => 'edit any entityform',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'edit any html_block content'.
  $permissions['edit any html_block content'] = array(
    'name' => 'edit any html_block content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any internship content'.
  $permissions['edit any internship content'] = array(
    'name' => 'edit any internship content',
    'roles' => array(
      'company consultant' => 'company consultant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any news content'.
  $permissions['edit any news content'] = array(
    'name' => 'edit any news content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any static_page content'.
  $permissions['edit any static_page content'] = array(
    'name' => 'edit any static_page content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit meta tags'.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'edit own html_block content'.
  $permissions['edit own html_block content'] = array(
    'name' => 'edit own html_block content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own internship content'.
  $permissions['edit own internship content'] = array(
    'name' => 'edit own internship content',
    'roles' => array(
      'company consultant' => 'company consultant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own news content'.
  $permissions['edit own news content'] = array(
    'name' => 'edit own news content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own static_page content'.
  $permissions['edit own static_page content'] = array(
    'name' => 'edit own static_page content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'manipulate all queues'.
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'manipulate queues'.
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: 'moderate content from draft to needs_review'.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to draft'.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to published'.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'schedule publishing of nodes'.
  $permissions['schedule publishing of nodes'] = array(
    'name' => 'schedule publishing of nodes',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: 'set own user location'.
  $permissions['set own user location'] = array(
    'name' => 'set own user location',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'location_user',
  );

  // Exported permission: 'submit latitude/longitude'.
  $permissions['submit latitude/longitude'] = array(
    'name' => 'submit latitude/longitude',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'location',
  );

  // Exported permission: 'switch shortcut sets'.
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'locale',
  );

  // Exported permission: 'use ipe with page manager'.
  $permissions['use ipe with page manager'] = array(
    'name' => 'use ipe with page manager',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels dashboard'.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels in place editing'.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use text format editor'.
  $permissions['use text format editor'] = array(
    'name' => 'use text format editor',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use workbench_moderation my drafts tab'.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'use workbench_moderation needs review tab'.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view all unpublished content'.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view all user locations'.
  $permissions['view all user locations'] = array(
    'name' => 'view all user locations',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'location_user',
  );

  // Exported permission: 'view any entityform'.
  $permissions['view any entityform'] = array(
    'name' => 'view any entityform',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'entityform',
  );

  // Exported permission: 'view moderation history'.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view own user location'.
  $permissions['view own user location'] = array(
    'name' => 'view own user location',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'location_user',
  );

  // Exported permission: 'view pane admin links'.
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view scheduled content'.
  $permissions['view scheduled content'] = array(
    'name' => 'view scheduled content',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'company consultant' => 'company consultant',
      'course provider' => 'course provider',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'view_blocked_users'.
  $permissions['view_blocked_users'] = array(
    'name' => 'view_blocked_users',
    'roles' => array(
      'company consultant' => 'company consultant',
      'editor' => 'editor',
    ),
    'module' => 'ulf_course_providers',
  );

  return $permissions;
}
