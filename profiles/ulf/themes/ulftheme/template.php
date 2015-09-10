<?php

/**
 * Implements hook_preprocess_page().
 */
function ulf_preprocess_page(&$variables) {
  // Provide main menu as block for all pages.
  $variables['main_menu_block'] = module_invoke('system', 'block_view', 'main-menu');
}


/**
 * Implements hook_preprocess_layout().
 */
function ulf_preprocess_front_page(&$variables) {
  // Provide newsletter block for front page.
  $variables['newsletter_block'] = module_invoke('mailchimp_signup', 'block_view', 'signup_to_newsletter');
}


/**
 * Implements theme_menu_tree().
 */
function ulf_menu_tree__main_menu ($variables) {
  // Strip default main menu tree of wrappers.
  return $variables['tree'];
}

/**
 * Implements theme_menu_tree().
 */
function ulf_menu_tree__menu_about_ulf ($variables) {
  // Strip default main menu tree of wrappers.
  return $variables['tree'];
}



/**
 * Implements theme_menu_link().
 */
function ulf_menu_link__main_menu($variables){
  $element = $variables['element'];
  $sub_menu = '';

  // Set type of link based on title of link.
  switch ($element['#title']) {
    case 'Dagtilbud':
      $element['#localized_options']['attributes']['class'][] = 'is-daycare';
      break;
    case 'Grundskole':
      $element['#localized_options']['attributes']['class'][] = 'is-school';
      break;
    case 'Ungdomsuddannelse':
      $element['#localized_options']['attributes']['class'][] = 'is-youth';
      break;
    case 'Kurser':
      $element['#localized_options']['attributes']['class'][] = 'is-course';
      break;
    case 'Om ULF':
      $menu_array = module_invoke('menu', 'block_view', 'menu-about-ulf');
      $element['#attributes']['class'][] = 'js-toggle-about';
      $sub_menu = '<div class="nav--sub js-about-menu is-hidden"><ul class="nav--static-pages is-menu">' . render($menu_array['content']) . '</ul></div>';
      break;
  }

  $element['#attributes']['class'][] = 'nav--list-item';
  $element['#localized_options']['attributes']['class'][] = 'nav--list-link';
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  return "<li" . drupal_attributes($element['#attributes']) . ">" . $output . $sub_menu . "</li>" ;
}


/**
 * Implements hook_preprocess_node().
 */
function ulf_preprocess_node(&$variables) {
  // Set default node teaser template.
  if ($variables['view_mode'] == 'teaser') {
    $variables['theme_hook_suggestions'][] = 'node__default_teaser';

    // Set teaser text.
    if ($variables['type'] == 'news') {
      $variables['teaser_content'] = ulf_teaser_filter($variables['content']['field_teaser']['0']['#markup']);
      $variables['theme_hook_suggestions'][] = 'node__news_teaser';
    }
    else {
      $variables['teaser_content'] = ulf_teaser_filter($variables['content']['field_full_description']['0']['#markup']);
    }
  }

  // Set default group type.
  $variables['group_type'] = 'course';

  // Provide variables for use in the different templates.
  switch ($variables['type']) { // Switch on content type.
    case 'course':
      if (!empty($variables['field_target_group'])) {

        // Get term id from target group field.
        if ($variables['view_mode'] == 'print') {
          $term = $variables['field_target_group']['und']['0']['tid'];
        }
        else {
          if (isset($variables['field_target_group']['0'])) {
            $term = $variables['field_target_group']['0']['taxonomy_term'];
          }
        }

        if (isset($term)) {
          $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
          $variables['group_type'] = strtolower($term_wrapper->name->value());
        }
      }
      break;
    case 'static_page':
      // Provide menu block for static page nodes.
      $variables['static_page_menu'] = module_invoke('menu', 'block_view', 'menu-about-ulf');

      // Provide newsletter block for static pages.
      $variables['newsletter_block'] = module_invoke('mailchimp_signup', 'block_view', 'signup_to_newsletter');
      break;

    case 'news':
      // Provide newsletter block for static pages.
      $variables['newsletter_block'] = module_invoke('mailchimp_signup', 'block_view', 'signup_to_newsletter');
      $variables['latest_news_titles'] = module_invoke('views', 'block_view', 'ulf_news_archive-block_1');
      $variables['group_type'] = 'news';
      break;
  }

  if (user_access('moderate content from needs_review to published') && arg(2) == 'draft') {
    $variables['display_workflow_actions'] =  TRUE;
  } else {
    $variables['display_workflow_actions'] =  FALSE;
  }

  // Fetch author.
  $variables['author'] = user_load($variables['uid']);
  $author_wrapper = entity_metadata_wrapper('user', $variables['author']);
  $variables['profile_name'] = $author_wrapper->field_profile_name->value();

  // Display author meta data on courses.
  if (($variables['type'] == 'course'|| $variables['type'] == 'course_educators') && ($variables['view_mode'] == 'full' || $variables['view_mode'] == 'print')) {
    $variables['profile_address'] = $author_wrapper->field_profile_address->value();
    $variables['profile_postal_code'] = $author_wrapper->field_profile_postal_code->value();
    $variables['profile_city'] = $author_wrapper->field_profile_city->value();
    $variables['profile_phone'] = $author_wrapper->field_profile_phone->value();
  }
}


/**
 * Implements hook_preprocess_user_profile().
 */
function ulf_preprocess_user_profile(&$variables) {
  // Enable a view for user profile templates.
  $variables['content_by_user'] = views_embed_view('ulf_content_by_user', 'block_1');
}


/**
 * Override or insert variables into the field template.
 */
function ulf_preprocess_field(&$variables) {
  // Some fields need all their html stripped, and want only the field value shown. We add a template for that.
  $stripped_template = array(
    'field_duration',
    'field_duration_unit',
    'field_profile_postal_code',
    'field_profile_city',
    'field_unit_price',
  );

  // Strip teaser fields.
  if ($variables['element']['#view_mode'] == 'teaser') {
    $stripped_template[] = 'field_period';
  }

  if (in_array($variables['element']['#field_name'], $stripped_template)) {
    $variables['theme_hook_suggestions'][] = 'field__stripped';
  }


  // Some fields should be displayed with label and content inline.
  $inline_template = array(
    'field_contact_phone',
    'field_profile_mail',
    'field_contact_office_hours',
  );

  $variables['display_type'] = 'is-block';
  if (in_array($variables['element']['#field_name'], $inline_template)) {
    $variables['display_type'] = 'is-inline';
  }

  // Change the "to" to "-" between from and to period.
  // @todo, find a better way.
  if ($variables['element']['#field_name'] == 'field_period') {
    $variables['items']['0']['#markup'] = str_replace(' til ', ' - ', $variables['items']['0']['#markup']);
  }

  // Display of teaser fields.
  if ($variables['element']['#view_mode'] == 'teaser' && $variables['element']['#field_type'] == 'taxonomy_term_reference' ) {
    $variables['theme_hook_suggestions'][] = 'field__taxonomy_term_reference__stripped';
  }
}


/**
 * Override or insert variables into the panel pane template.
 *
 */
function ulf_preprocess_panels_pane(&$variables) {
  // Suggestions based on sub-type.
  $variables['theme_hook_suggestions'][] = 'panels_pane__' . str_replace('-', '__', $variables['pane']->subtype);
  $variables['theme_hook_suggestions'][] = 'panels_pane__'  . $variables['pane']->panel . '__' . str_replace('-', '__', $variables['pane']->subtype);

  // Frontpage panes.
  if ($variables['is_front'] && !empty($variables['pane']->panel)) {
    $variables['theme_hook_suggestions'][] = 'panels_pane__front';
  }

  // We only want to use the class provided from the ui.
  $variables['provided_class'] = '';
  if(!empty($variables['pane']->css['css_class'])) {
    $variables['provided_class'] = $variables['pane']->css['css_class'];
  }
}


/**
 * Implements theme_panels_default_style_render_region().
 *
 * Remove the panel separator from the default rendering method.
 */
function ulf_panels_default_style_render_region($variables) {
  $output = '';
  $output .= implode('', $variables['panes']);
  return $output;
}


/**
 * Implements theme_links().
 */
function ulf_links__system_main_menu($variables) {
  $html = '';

  foreach ($variables['links'] as $link) {
    // The \n after the <li> tag is important when using display: inline-block.
    $html .= '<li class="nav--list-item">' . l($link['title'], $link['href'], $link) . '</li>' . "\n";
  }

  return $html;
}

/**
 * Implements theme_links().
 */
function ulf_menu_link__menu_about_ulf($variables) {
  $element = $variables ['element'];
  $sub_menu = '';
  $element['#attributes']['class'] = 'nav--static-pages-item';

  if ($element ['#below']) {
    $sub_menu = drupal_render($element ['#below']);
  }
  $output = l($element ['#title'], $element ['#href'], $element ['#localized_options']);
  return '<li' . drupal_attributes($element ['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


/**
 * Implements theme_item_list().
 */
function ulf_item_list($variables) {
  $items = $variables ['items'];
  $title = $variables ['title'];
  $type = $variables ['type'];
  $attributes = $variables ['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes [$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 1) {
        $attributes ['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes ['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

function ulf_file_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $url = file_create_url($file->uri);
  $icon = theme('file_icon', array('file' => $file, 'icon_directory' => $icon_directory));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $options = array(
    'attributes' => array(
      'type' => $file->filemime . '; length=' . $file->filesize,
      'target' => '_blank',
    ),
  );

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }

  return '<span class="file">' . $icon . ' ' . l($link_text, $url, $options) . '</span>';
}


function ulf_teaser_filter($str) {
  // Clean out headlines.
  $str = strip_tags($str);


    // Trim string to word boundry.
    $trimmed = substr($str, 0, 100);
    if (strlen($str) > 100) {
      $trimmed = $trimmed . '...';
    }

    return $trimmed;
}