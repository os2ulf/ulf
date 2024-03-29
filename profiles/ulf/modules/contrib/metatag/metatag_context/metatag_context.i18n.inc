<?php

/**
 * @file
 * Internationalization (i18n) hooks.
 */

/**
 * Implements hook_i18n_object_info().
 */
function metatag_context_i18n_object_info() {
  $info['metatag_context'] = array(
    'title' => t('Metatag:Context configurations'),
    // Callback to load all config objects.
    'list callback' => 'metatag_context_i18n_list_contexts',
    // The object load callback.
    // @code
    // 'load callback' => 'metatag_context_i18n_load',
    // @endcode
    // @todo Custom i18n object overrides.
    // @code
    // 'class' => 'metatag_context_i18n_metatag'
    // @endcode
    // @todo Is this needed? What does it do?
    // @code
    // 'translation set' => TRUE
    // @endcode
    // The object key field.
    'key' => 'name',
    // Placeholders for automatic paths. This connects the 'key' to strings in
    // the paths listed below.
    // @code
    // 'placeholders' => array(
    //   '%name' => 'name',
    // ),
    // @endcode
    // To produce edit links automatically.
    // @code
    // 'edit path' => 'admin/config/search/metatags/config/%instance',
    // @endcode
    // Auto-generate a 'translate' tab.
    // @code
    // 'translate tab' => 'admin/config/search/metatags/config/%instance/translate',
    // @endcode
    // Properties for string translation.
    'string translation' => array(
      // The textgroup, type and (below) name will be concatenated into a single
      // string as the {locales_source} context.
      'textgroup' => 'metatag',
      'type' => 'metatag_context',
      // Table where the object is stored, to automate string lists.
      'table' => 'context',
      // Translatable properties of these objects, this will be added later.
      'properties' => array(),
      // The path to translate individual strings.
      // @code
      // 'translate path' => 'admin/config/search/metatags/config/%instance/translate/%i18n_language',
      // @endcode
    ),
  );

  // Compile all of the tags to add to the translation stack.
  $meta_tag_info = metatag_get_info();
  $groups = $meta_tag_info['groups'];
  foreach ($meta_tag_info['tags'] as $tag_info) {
    // Ignore certain field types that aren't translatable, mostly fields that
    // list predetermined options in various forms.
    if (!empty($tag_info['class']) && $tag_info['class'] == 'DrupalListMetaTag') {
      continue;
    }
    elseif (!empty($tag_info['form']['#type']) && $tag_info['form']['#type'] == 'select') {
      continue;
    }
    elseif (!empty($tag_info['form']['#options'])) {
      continue;
    }

    // Build a suitable structure for this meta tag.
    $tag_name = $tag_info['name'];
    $title = $tag_info['label'];
    if (!empty($tag_info['group'])) {
      $tag_group = $tag_info['group'];
      if (empty($groups[$tag_group]['label'])) {
        $tag_group = $groups[$tag_group]['label'];
      }
      $title = $tag_group . ': ' . $title;
    }

    $info['metatag_context']['string translation']['properties'][$tag_name] = array(
      'title' => $title,
      'field' => "reactions.metatag_context_reaction.und.{$tag_name}.value",
    );
  }

  return $info;
}

/**
 * Implements hook_i18n_string_list().
 */
function metatag_context_i18n_string_list($group) {
  // @todo Functionality to delete translation records when Panels are deleted.
  if ($group == 'metatag' || $group == 'all') {
    $strings = array();

    foreach (context_context_list() as $context_name) {
      $context = context_load($context_name);
      if (!empty($context->reactions['metatag_context_reaction']['metatags'][LANGUAGE_NONE])) {
        $new_strings = array();
        foreach ($context->reactions['metatag_context_reaction']['metatags'][LANGUAGE_NONE] as $name => $value) {
          if (isset($value['value'])) {
            // Don't translate meta tags that are arrays.
            if (is_array($value['value'])) {
              continue;
            }
            // Collapse the array down one level.
            else {
              $new_strings[$name] = $value['value'];
            }
          }
        }
        $strings['metatag']['metatag_context'][$context->name] = $new_strings;
      }
    }

    return $strings;
  }
}

/**
 * List callback.
 */
function metatag_context_i18n_list_contexts() {
  ctools_include('export');
  $configs = ctools_export_crud_load_all('metatag_config');
  if (!empty($configs)) {
    // Unserialize the config array.
    foreach ($configs as &$config) {
      if (is_string($config->config)) {
        $config->config = metatag_data_decode($config->config);
      }
    }
    return $configs;
  }
}
