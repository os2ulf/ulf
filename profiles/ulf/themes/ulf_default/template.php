<?php
/**
 * @file
 * Processes content before the templates.
 */

/**
 * Implements hook_preprocess_html().
 */
function ulf_default_preprocess_html(&$variables) {
  // Set Open Graph tags for nodes.
  if (isset($variables['page']['content']['system_main']['nodes'])
    && count(
      $variables['page']['content']['system_main']['nodes']
    ) > 0
  ) {
    $nodes = $variables['page']['content']['system_main']['nodes'];
    $node = reset($nodes);

    $meta_description = [
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => [
        'name' => 'og:title',
        'content' => $variables['head_title_array']['title'],
      ],
    ];
    drupal_add_html_head($meta_description, 'meta_title');

    $imagePath = !empty($node['field_image']) ? image_style_url(
      'facebook_open_graph',
      $node['field_image'][0]['#item']['uri']
    ) : '';

    $meta_description['#attributes']['name'] = 'og:image';
    $meta_description['#attributes']['content'] = $imagePath;
    drupal_add_html_head($meta_description, 'meta_image');

    if (isset($node['#node']->field_full_description['und'][0]['value'])) {
      $meta_description['#attributes']['name'] = 'og:description';
      $teaser = str_replace(
        '&nbsp;',
        '',
        strip_tags(
          $node['#node']->field_full_description['und'][0]['value']
        )
      );
      $meta_description_cut = substr($teaser, 0, strpos($teaser, '.')) . '...';
      $meta_description['#attributes']['content'] = $meta_description_cut;

      drupal_add_html_head($meta_description, 'meta_description');
    }

    $meta_description['#attributes']['name'] = 'og:url';
    $meta_description['#attributes']['content']
      = url(current_path(), ['absolute' => TRUE]);
    drupal_add_html_head($meta_description, 'meta_url');

    $meta_description['#attributes']['name'] = 'og:locale';
    $meta_description['#attributes']['content'] = 'da_DK';
    drupal_add_html_head($meta_description, 'meta_locale');
  }

  if (isset($variables['page']['content']['system_main']['field_profile_name']['0']['#markup'])) {
    $variables['head_title']
      = $variables['page']['content']['system_main']['field_profile_name']['0']['#markup']
      . ' | ' . $variables['head_title_array']['name'];
  }
}

/**
 * Implements hook_preprocess_page().
 */
function ulf_default_preprocess_page(&$variables) {
  // Check theme.
  if (isset($GLOBALS['theme_info']->base_theme)
    && $GLOBALS['theme_info']->base_theme == 'ulf_default'
  ) {
    $variables['theme_overridden'] = TRUE;
    $variables['active_theme'] = $GLOBALS['theme_info']->name;
    $variables['base_theme'] = $GLOBALS['theme_info']->base_theme;
  }

  // Hamburger icon.
  $variables['hamburger_icon_path'] = $variables['directory'];

  // Provide main menu as block for all pages.
  $variables['main_menu_block']
    = module_invoke('system', 'block_view', 'main-menu');


  // Add social media links to header if selected.
  if (variable_get('ulf_social_media_header', FALSE) == TRUE) {
    $variables['social_media_links']
      = module_invoke('ulf_social_media', 'block_view', 'ulf_social_media');
  }

  // Add social media links to header if selected.
  if (variable_get('footer_siteinfo', FALSE) == TRUE) {
    $variables['siteinfo'] = variable_get('footer_siteinfo', FALSE);
  }
}

/**
 * Implements hook_preprocess_layout().
 */
function ulf_default_preprocess_front_page(&$variables) {
  $variables['empty_regions'] = [];
  foreach ($variables['display']->content as $pane) {
    if (property_exists($pane, 'IPE_empty')) {
      $variables['empty_regions'][] = $pane->pid;
    }
  }
}

/**
 * Implements theme_menu_tree().
 */
function ulf_default_menu_tree__main_menu($variables) {
  // Strip default main menu tree of wrappers.
  return $variables['tree'];
}

/**
 * Implements theme_menu_tree().
 */
function ulf_default_menu_tree__menu_about_ulf($variables) {
  // Strip default main menu tree of wrappers.
  return $variables['tree'];
}

/**
 * Implements theme_menu_link().
 */
function ulf_default_menu_link__main_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  // If item is a parent.
  if ($element['#below']) {
    $element['#attributes']['class'][] = 'js-toggle-expanded';
    $element['#attributes']['mlid'][] = $element['#original_link']['mlid'];
    $sub_menu = '<div class="nav--sub js-expanded-menu-'
      . $element['#original_link']['mlid']
      . ' is-hidden"><ul class="nav--static-pages is-menu">' . drupal_render(
        $element['#below']
      ) . '</ul></div>';
  }
  // If item is a child.
  if ($element['#original_link']['plid'] > 0) {
    $element['#attributes']['class'][] = 'nav--list-item-sub';
  }
  else {
    $element['#attributes']['class'][] = 'nav--list-item';
    $element['#localized_options']['attributes']['class'][] = 'nav--list-link';
  }

  $link
    = l($element['#title'], $element['#href'], $element['#localized_options']);

  return "<li" . drupal_attributes($element['#attributes']) . ">" . $link
    . $sub_menu
    . "</li>";
}

/**
 * Implements hook_preprocess_node().
 */
function ulf_default_preprocess_node(&$variables) {
  // Set default node teaser template.
  if ($variables['view_mode'] == 'teaser') {
    $variables['theme_hook_suggestions'][] = 'node__default_teaser';

    // Set teaser text and new teaser template suggestion for news.
    if ($variables['type'] == 'news'
      || $variables['type'] == 'news_course_provider'
    ) {
      $variables['teaser_content'] = _ulf_default_teaser_filter(
        $variables['content']['field_teaser']['0']['#markup']
      );
      $variables['theme_hook_suggestions'][] = 'node__news_teaser';
    }
    else {
      $variables['teaser_content'] = _ulf_default_teaser_filter(
        $variables['content']['field_full_description']['0']['#markup']
      );
    }

    // Select first 3 field_relevance_educators values and prepare for print.
    if ($variables['type'] == 'course_educators') {
      $target_group_array = [];
      if (!empty($variables['field_relevance_educators'])) {
        foreach (
          $variables['field_relevance_educators'] as $target_group
        ) {
          $uri = taxonomy_term_uri($target_group['taxonomy_term']);
          $target_group_array[] = '<a href="' . $uri['path'] . '">'
            . $target_group['taxonomy_term']->name . '</a>';
        }
      }
      $sliced_target_group_array = array_slice($target_group_array, 0, 3);

      $variables['course_teaser_target_group'] = '';
      foreach ($sliced_target_group_array as $value) {
        $variables['course_teaser_target_group'] .= $value . ', ';
      }

      if (count($target_group_array) > 3) {
        $variables['course_teaser_target_group'] .= '(...)';
      }
    }
  }

  // Set a default group type.
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

      // Add view for displaying target group sub
      $variables['view__target_group_sub'] = module_invoke(
        'views',
        'block_view',
        'ulf_course_target_groups-block_1'
      );


      // Display of duration remove 0's in decimal.
      if (isset($variables['content']['field_duration']['0']['#markup'])) {
        $variables['stripped_duration'] = preg_replace(
          '/[,\.]?0+$/',
          '',
          $variables['content']['field_duration']['0']['#markup']
        );
      }
      break;

    case 'course_educators':
      // Display of duration remove 0's in decimal.
      if (isset($variables['content']['field_duration']['0']['#markup'])) {
        $variables['stripped_duration'] = preg_replace(
          '/[,\.]?0+$/',
          '',
          $variables['content']['field_duration']['0']['#markup']
        );
      }
      break;

    case 'static_page':
      // Provide menu block for static page nodes.
      $variables['static_page_menu']
        = module_invoke('menu_block', 'block_view', 'ulf_base-1');
      if (empty($variables['static_page_menu']['content'])) {
        $variables['static_page_menu'] = FALSE;
      }
      // Provide newsletter block for static pages.
      $variables['newsletter_block'] = module_invoke(
        'mailchimp_signup',
        'block_view',
        'signup_to_newsletter'
      );
      break;

    case 'news':
    case 'news_course_provider':
      // Provide newsletter block for news pages.
      $variables['newsletter_block'] = module_invoke(
        'mailchimp_signup',
        'block_view',
        'signup_to_newsletter'
      );
      $variables['latest_news_titles']
        = module_invoke('views', 'block_view', 'ulf_news_archive-block_1');
      $variables['group_type'] = 'news';
      break;
    case 'education':
    case 'internship':
      // Add view for displaying target group sub
      $variables['view__target_group_sub'] = module_invoke(
        'views',
        'block_view',
        'ulf_course_target_groups-block_1'
      );

      // Display of duration remove 0's in decimal.
      if (isset($variables['content']['field_duration']['0']['#markup'])) {
        $variables['stripped_duration']
          = rtrim($variables['content']['field_duration']['0']['#markup'], ',.0');
      }
      $variables['group_type'] = $variables['type'];
      break;
  }

  // Add publishing action
  if (user_access('moderate content from needs_review to published')
    && arg(2) == 'draft'
  ) {
    $variables['display_workflow_actions'] = TRUE;
  }
  else {
    $variables['display_workflow_actions'] = FALSE;
  }

  // Fetch author.
  $variables['author'] = user_load($variables['uid']);
  $author_wrapper = entity_metadata_wrapper('user', $variables['author']);
  $variables['profile_name'] = $author_wrapper->field_profile_name->value();
  if ($author_wrapper->__isset('field_garantipartner')) {
    $variables['garantipartner']
      = $author_wrapper->field_garantipartner->value();
  }

  // Display author meta data for courses.
  if (($variables['type'] == 'course'
      || $variables['type'] == 'internship'
      || $variables['type'] == 'education'
      || $variables['type'] == 'course_educators'
      || $variables['type'] == 'news_course_provider')
    && ($variables['view_mode'] == 'full'
      || $variables['view_mode'] == 'print')
  ) {

    $variables['profile_phone'] = $author_wrapper->field_profile_phone->value();
    $variables['profile_home_page']
      = $author_wrapper->field_profile_home_page->value()['url'];

    // Fetch location information from the user. Used in the information box to
    // the right when displaying the profile.
    $account = $variables['author'];
    $variables['profile_address'] = isset($account->location['street'])
      ? $account->location['street']
      : '';
    $variables['profile_postal_code'] = isset($account->location['postal_code'])
      ? $account->location['postal_code'] : '';
    $variables['profile_city'] = isset($account->location['city'])
      ? $account->location['city'] : '';
  }

  // Transport application form
  $variables['transport_form'] = module_exists('transportpulje_form') ? TRUE
    : FALSE;

  // Set default node teaser template.
  if ($variables['view_mode'] == 'teaser') {
    //    $variables['theme_hook_suggestions'][] = 'node__default_teaser';

    // Select first 3 field_relevance_educators values and prepare for print.
    if ($variables['type'] == 'course_educators') {
      $target_group_array = [];
      if (!empty($variables['field_relevance_educators'])) {
        foreach (
          $variables['field_relevance_educators'] as $target_group
        ) {
          $target_group_array[] = $target_group['taxonomy_term']->name;
        }
      }
      $sliced_target_group_array = array_slice($target_group_array, 0, 3);

      $variables['course_teaser_target_group'] = '';
      foreach ($sliced_target_group_array as $value) {
        $variables['course_teaser_target_group'] .= $value . ', ';
      }

      if (count($target_group_array) > 3) {
        $variables['course_teaser_target_group'] .= '(...)';
      }
    }
  }
}

/**
 * Implements hook_preprocess_user_profile().
 */
function ulf_default_preprocess_user_profile(&$variables) {
  // Enable a view for user profile templates.
  $variables['content_by_user_daycare']
    = views_embed_view('ulf_content_by_user', 'block_4');
  $variables['content_by_user_school']
    = views_embed_view('ulf_content_by_user', 'block_3');
  $variables['content_by_user_youth']
    = views_embed_view('ulf_content_by_user', 'block_1');
  $variables['content_by_user_courses']
    = views_embed_view('ulf_content_by_user', 'block_2');
  $variables['content_by_user_news']
    = views_embed_view('ulf_content_by_user', 'block');

  // Fetch location information from the user. Used in the information box to
  // the right when displaying the profile.
  $account = $variables['elements']['#account'];
  $variables['location'] = [
    'name' => isset($account->location['name']) ? $account->location['name']
      : NULL,
    'street' => isset($account->location['street'])
      ? $account->location['street'] : NULL,
    'postal_code' => isset($account->location['postal_code'])
      ? $account->location['postal_code'] : NULL,
    'city' => isset($account->location['city']) ? $account->location['city']
      : NULL,
  ];
}

/**
 * Implements hook_preprocess_field().
 */
function ulf_default_preprocess_field(&$variables) {
  // Some fields need all their html stripped, and want only the field value shown. We add a template for that.
  $stripped_template = [
    'field_duration',
    'field_duration_unit',
    'field_unit_price',
    'field_price_description',
    'field_duration_description',
    'field_count_description',
  ];

  if ($variables['element']['#field_name'] == 'field_relevance_educators') {
    $items = $variables['element']['#items'];

    // Get parents for taxonomy terms.
    foreach ($items as $item) {
      $term = taxonomy_term_load($item['tid']);
      $query = db_select('taxonomy_term_hierarchy', 'tth')
        ->fields('tth', ['parent'])
        ->condition('tth.tid', $item['tid']);
      $parents = $query->execute()->fetchCol();
      if (count($parents) == 1) {
        $parents = reset($parents);
      }
      $term->parent = $parents;
    }

    // Create hierarchy array.
    $hierarchy = [];
    foreach ($items as $item) {
      $hierarchy[$item['taxonomy_term']->parent][] = $item;
    }

    // Render hierarchy.
    $rendered_items = [];
    foreach ($hierarchy[0] as $item) {
      $rendered_items[] = [
        '#markup' => $item['taxonomy_term']->name,
      ];

      if (isset($hierarchy[$item['tid']])) {
        foreach ($hierarchy[$item['tid']] as $sub_item) {
          $rendered_items[] = [
            '#markup' => '&nbsp;- ' . $sub_item['taxonomy_term']->name,
          ];
        }
      }
    }

    // Override rendering.
    $variables['items'] = $rendered_items;

  }

  if ($variables['element']['#field_name'] == 'field_paragraph_hero_title') {
    $element = $variables['element']['#object'];

    if (isset($element->field_paragraph_main_headline)) {
      $variables['is_main']
        = $element->field_paragraph_main_headline['und'][0]['value'];
    }

    $variables['tag'] = ($variables['is_main'] === '1') ? 'h1' : 'h2';
  }

  // Strip teaser fields.
  if ($variables['element']['#view_mode'] == 'teaser') {
    $stripped_template[] = 'field_period';
  }

  // Provide template suggestion for stripped fields.
  if (in_array($variables['element']['#field_name'], $stripped_template)) {
    $variables['theme_hook_suggestions'][] = 'field__stripped';
  }

  // Some fields should be displayed with label and content inline.
  $inline_template = [
    'field_contact_phone',
    'field_profile_mail',
  ];

  $variables['display_type'] = 'is-block';
  if (in_array($variables['element']['#field_name'], $inline_template)) {
    $variables['display_type'] = 'is-inline';
  }

  // Change the "to" to "-" between from and to period.
  // @todo, find a better way.
  if ($variables['element']['#field_name'] == 'field_period') {
    $variables['items']['0']['#markup']
      = str_replace(' til ', ' - ', $variables['items']['0']['#markup']);
  }

  // Display of teaser fields.
  if ($variables['element']['#view_mode'] == 'teaser'
    && $variables['element']['#field_type'] == 'taxonomy_term_reference'
  ) {
    $variables['theme_hook_suggestions'][]
      = 'field__taxonomy_term_reference__stripped';
  }

  if ($variables['element']['#field_name'] == 'field_paragraph_button') {
    foreach ($variables['items'] as $key => $item) {
      $variables['items'][$key]['#element']['attributes']['class'] = 'btn';
    }
  }
}

/**
 * Implements hook_preprocess_panels_pane().
 */
function ulf_default_preprocess_panels_pane(&$variables) {
  // Suggestions based on sub-type.
  $variables['theme_hook_suggestions'][] = 'panels_pane__'
    . str_replace('-', '__', $variables['pane']->subtype);
  $variables['theme_hook_suggestions'][] = 'panels_pane__'
    . $variables['pane']->panel . '__' . str_replace(
      '-',
      '__',
      $variables['pane']->subtype
    );

  // Frontpage panes.
  if ($variables['is_front'] && !empty($variables['pane']->panel)) {
    $variables['theme_hook_suggestions'][] = 'panels_pane__front';
  }

  // Two split panes.
  if ($variables['display']->layout == 'two_split') {
    $variables['theme_hook_suggestions'][] = 'panels_pane__'
      . $variables['display']->layout . '__' . str_replace(
        "-",
        "_",
        $variables['pane']->subtype
      );
  }

  // We only want to use the class provided from the ui.
  $variables['provided_class'] = '';
  if (!empty($variables['pane']->css['css_class'])) {
    $variables['provided_class'] = $variables['pane']->css['css_class'];
  }
  if ($variables['pane']->subtype == 'group_course') {
    // Provide newsletter block for front page.
    $variables['newsletter_block'] = module_invoke(
      'mailchimp_signup',
      'block_view',
      'signup_to_newsletter'
    );
  }
}

/**
 * Implements theme_panels_default_style_render_region().
 *
 * Remove the panel separator from the default rendering method.
 */
function ulf_default_panels_default_style_render_region($variables) {
  $output = '';
  $output .= implode('', $variables['panes']);

  return $output;
}

/**
 * Implements theme_links().
 */
function ulf_default_links__system_main_menu($variables) {
  $html = '';

  foreach ($variables['links'] as $link) {
    // The \n after the <li> tag is important when using display: inline-block.
    $html .= '<li class="nav--list-item">' . l(
        $link['title'],
        $link['href'],
        $link
      ) . '</li>' . "\n";
  }

  return $html;
}

/**
 * Implements theme_links().
 */
function ulf_default_menu_link__menu_about_ulf($variables) {
  $element = $variables ['element'];
  $sub_menu = '';
  $element['#attributes']['class'] = 'nav--static-pages-item';

  if ($element ['#below']) {
    $sub_menu = drupal_render($element ['#below']);
  }
  $output = l(
    $element ['#title'],
    $element ['#href'],
    $element ['#localized_options']
  );

  return '<li' . drupal_attributes($element ['#attributes']) . '>' . $output
    . $sub_menu . "</li>\n";
}

/**
 * Implements theme_item_list().
 */
function ulf_default_item_list($variables) {
  $is_pager = (in_array('pager', $variables['attributes']['class'])) ? TRUE
    : FALSE;

  $items = $variables ['items'];
  $title = $variables ['title'];
  $type = $variables ['type'];
  $attributes = $variables ['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';

  if ($is_pager) {
    $output .= '<div class="pager-wrapper"><div class="pagination">';
  }

  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = [];
      $children = [];
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
        $data .= theme_item_list(
          [
            'items' => $children,
            'title' => NULL,
            'type' => $type,
            'attributes' => $attributes,
          ]
        );
      }
      if ($i == 1) {
        $attributes ['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes ['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data
        . "</li>\n";
    }
    $output .= "</$type>";
  }

  if ($is_pager) {
    $output .= '</div></div>';
  }

  return $output;
}

/**
 * Implements theme_date_display_range().
 */
function ulf_default_date_display_range($variables) {
  $date1 = $variables['date1'];
  $date2 = $variables['date2'];
  $timezone = $variables['timezone'];
  $attributes_start = $variables['attributes_start'];
  $attributes_end = $variables['attributes_end'];
  $show_remaining_days = $variables['show_remaining_days'];

  $start_date = '<span class="date-display-start"'
    . drupal_attributes($attributes_start)
    . '>' . $date1 . '</span>';
  $end_date = '<span class="date-display-end"'
    . drupal_attributes($attributes_end) . '>'
    . $date2 . $timezone . '</span>';

  // If microdata attributes for the start date property have been passed in,
  // add the microdata in meta tags.
  if (!empty($variables['add_microdata'])) {
    $start_date .= '<meta' . drupal_attributes(
        $variables['microdata']['value']['#attributes']
      ) . '/>';
    $end_date .= '<meta' . drupal_attributes(
        $variables['microdata']['value2']['#attributes']
      ) . '/>';
  }

  // Wrap the result with the attributes.
  $output = t(
    '!start-date to !end-date',
    [
      '!start-date' => $start_date,
      '!end-date' => $end_date,
    ]
  );

  // Add remaining message and return.
  return $output . $show_remaining_days;
}

/**
 * Implements hook_file_link().
 */
function ulf_default_file_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $url = file_create_url($file->uri);
  $icon = theme(
    'file_icon',
    ['file' => $file, 'icon_directory' => $icon_directory]
  );

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $options = [
    'attributes' => [
      'type' => $file->filemime . '; length=' . $file->filesize,
      'target' => '_blank',
    ],
  ];

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }

  return '<span class="file">' . $icon . ' ' . l($link_text, $url, $options)
    . '</span>';
}

/**
 * A custom function for striping html for node teasers
 *
 * @param $str
 *   The string to strip.
 *
 * @return string
 *  The stripped string.
 */
function _ulf_default_teaser_filter($str) {
  // Clean out headlines.
  $str = strip_tags($str);

  // Trim string to word boundary.
  $trimmed = substr($str, 0, 100);
  if (strlen($str) > 100) {
    $trimmed = $trimmed . '...';
  }

  return $trimmed;
}

/**
 * Form alter
 */
function ulf_default_form_mailchimp_signup_subscribe_block_signup_to_newsletter_form_alter(
  &$form,
  &$form_state,
  $form_id
) {
  $form['mergevars']['EMAIL']['#attributes']['placeholder'] = t('Email');
}

/**
 * Implements hook_views_post_render().
 */
function ulf_default_views_post_render(&$view, &$output, &$cache) {
  // Modify the target groups to collapse "X. klasse" to ranges.
  if ($view->name == 'ulf_course_target_groups') {
    $classes = [];
    $years = [];
    $other_results = [];

    foreach ($view->result as $result) {
      if (!empty($result->_entity_properties['field_target_group_sub_tid:entity object'])) {
        $name
          = $result->_entity_properties['field_target_group_sub_tid:entity object']->name;

        if (preg_match('/.{1,2} år/', $name)) {
          $years[] = str_replace(' år', '', $name);
        }
        else {
          if (preg_match('/.{1,2}\. klasse/', $name)) {
            $classes[] = str_replace('. klasse', '', $name);
          }
          else {
            $other_results[] = $name;
          }
        }
      }
    }

    $ranges = _ulf_default_create_ranges($classes, '. klasse', '. - ');
    $yearRanges = _ulf_default_create_ranges($years, ' år');

    $output = '';

    if (!empty($ranges)) {
      $output .= implode('<br>', $ranges) . '<br>';
    }

    if (!empty($yearRanges)) {
      $output .= implode('<br>', $yearRanges) . '<br>';
    }

    if (!empty($other_results)) {
      $output .= implode('<br>', $other_results);
    }
  }
}

/**
 * Creates X. klasse ranges from array of numbers.
 *
 * @param $arr
 *   Array of numbers.
 *
 * @return array
 */
function _ulf_default_create_ranges($arr, $stringEnd, $separator = ' - ') {
  if (empty($arr)) {
    return $arr;
  }

  asort($arr);

  $ranges = [];
  $rangeStart = NULL;
  $current = NULL;
  $currentEntry = NULL;;

  foreach ($arr as $key => $entry) {
    $currentEntry = (int) $entry;

    if (is_null($rangeStart)) {
      $rangeStart = $currentEntry;
      $current = $currentEntry;
      continue;
    }

    if ($entry-1 == $current) {
      $current = $currentEntry;
      continue;
    }
    else {
      if ($rangeStart < $current) {
        $ranges[] = $rangeStart . $separator . $current . $stringEnd;
      }
      else {
        $ranges[] = $rangeStart . $stringEnd;
      }
      $rangeStart = $currentEntry;
      $current = $currentEntry;
    }
  }

  if ($rangeStart < $current) {
    $ranges[] = $rangeStart . $separator . $current . $stringEnd;
  }
  else {
    $ranges[] = $rangeStart . $stringEnd;
  }

  return $ranges;
}


/***********************************
 * Page builder
 **********************************/

/**
 * Implements hook_preprocess_entity().
 */
function ulf_default_preprocess_entity(&$variables) {
  if ($variables['entity_type'] === 'paragraphs_item') {

    $bundle = $variables['elements']['#bundle'];

    switch ($bundle) {
      case 'hero':
        $url
          = image_style_url('hero', $variables['content']['field_paragraph_background_image'][0]['#item']['uri']);
        $variables['attributes_array']['style'] = 'background-image: url("'
          . $url . '")';

        $variables['content_attributes_array']['class'] = [
          'hero--content',
        ];

        if (isset($variables['field_textbox_color'])) {
          $textbox_color = $variables['field_textbox_color'][0]['value'];
          $variables['content_attributes_array']['class'][]
            = 'hero--content--theme__' . $textbox_color;
        }

        if (isset($variables['field_paragraph_inner_padding'])) {
          $inner_padding
            = $variables['field_paragraph_inner_padding'][0]['value'];
          $variables['content_attributes_array']['class'][]
            = 'hero--content--padding__' . $inner_padding;
        }

        break;
      case 'spacer':
        $space = $variables['field_paragraph_spacing'][0]['value'] ?? 'medium';
        $hr = $variables['field_paragraph_hr'][0]['value'] ?? FALSE;
        $variables['classes_array'][] = 'paragraphs-item-spacer--' . $space;

        if ($hr) {
          $variables['classes_array'][] = 'paragraphs-item-spacer--hr';
        }
      case 'appetizer':
      case 'text_with_image':
        $button = $variables['paragraphs_item']->field_paragraph_button ?? NULL;
        $show_button = $variables['paragraphs_item']->field_paragraph_show_cta ?? NULL;

        if (!$show_button !== NULL) {
          $variables['show_button'] = (bool) ($show_button[LANGUAGE_NONE][0]['value'] ?? NULL);
        }

        if ($button) {
          $link = [
            '#theme' => 'link',
            '#text' => render($variables['content']['field_paragraph_image']),
            '#path' => $button[LANGUAGE_NONE][0]['url'] ?? NULL,
            '#options' => [
              'attributes' => $button[LANGUAGE_NONE][0]['attributes'],
              //REQUIRED:
              'html' => TRUE,
            ],
          ];
          $variables['content']['field_paragraph_image'] = $link;
        }
        break;
      case 'text_with_video':
        $variables['show_button']
          = (bool) ($variables['paragraphs_item']->field_paragraph_show_cta[LANGUAGE_NONE][0]['value']
          ?? NULL);
        break;
      case 'image_with_link':
        // Handle background image with opacity.
        $paragraph_bg_color = $variables['paragraphs_item']->field_paragraph_bg_color ?? NULL;
        $colorName = $paragraph_bg_color[LANGUAGE_NONE][0]['rgb'] ?? NULL;
        if ($colorName !== NULl) {
          $colorName = ltrim($colorName, '#');
          [$r, $g, $b] = array_map('hexdec', str_split($colorName, 2));
          $background_color = "rgba({$r},{$g},{$b}, 0.7)";
        }
        $paragraph_link_field = $variables['paragraphs_item']->field_paragraph_button ?? NULL;
        $paragraph_link = $paragraph_link_field[LANGUAGE_NONE][0]['original_url'];
        $variables['content']['paragraph_link'] = $paragraph_link;
        break;
      case 'news_list':
        $view = views_get_view('ulf_frontpage_news');
        $variables['news_list'] = $view->preview('panel_pane_1');
        break;
    }

    if (module_exists('color_field')) {
      $styles = [];
      // Add background color if exists
      $paragraph_bg_color
        = $variables['paragraphs_item']->field_paragraph_bg_color ?? NULL;
      $paragraph_border_color
        = $variables['paragraphs_item']->field_paragraph_border_color ?? NULL;
      $paragraph_text_color
        = $variables['paragraphs_item']->field_paragraph_text_color ?? NULL;
      if (!empty($paragraph_bg_color) || !empty($paragraph_border_color)) {
        if (!isset($background_color)) {
          $background_color = $paragraph_bg_color[LANGUAGE_NONE][0]['rgb'] ?? NULL;
        }
        $border_color = $paragraph_border_color[LANGUAGE_NONE][0]['rgb'] ??
          NULL;
        $text_color = $paragraph_text_color[LANGUAGE_NONE][0]['rgb'] ?? NULL;
        if (!empty($background_color)) {
          $styles[] = 'background-color:' . $background_color;
          $variables['classes_array'][] = 'paragraphs-item-'
            . str_replace('_', '-', $bundle) . '--has-background';
        }

        if (!empty($border_color)) {
          $styles[] = 'border-color:' . $border_color;
          $variables['classes_array'][] = 'paragraphs-item-'
            . str_replace('_', '-', $bundle) . '--has-border';
        }

        if (!empty($text_color)) {
          $styles[] = 'color:' . $text_color;

          switch ($text_color) {
            case '#FFFFFF':
              $variables['classes_array'][]
                = 'paragraphs-item--text-color__negative';
              break;
          }

          $variables['classes_array'][] = 'paragraphs-item-'
            . str_replace('_', '-', $bundle) . '--has-text-color';
        }
      }

      if (!empty($styles)) {
        $variables['attributes_array']['style'] = implode(';', $styles);
      }
    }

    $paragraph_alignment
      = $variables['paragraphs_item']->field_paragraph_alignment ?? NULL;

    if ($paragraph_alignment !== NULL
      && isset($paragraph_alignment[LANGUAGE_NONE])
    ) {
      $variables['classes_array'][] = 'paragraphs-item--alignment-'
        . $paragraph_alignment[LANGUAGE_NONE][0]['value'];
    }
  }
}

function ulf_default_file_icon($variables) {
  $file = $variables['file'];
  $icon_directory = drupal_get_path('theme', 'ulf_default') . '/icons';
  $mime = check_plain($file->filemime);
  $icon_url = file_icon_url($file, $icon_directory);
  return '<img class="file-icon" alt="" title="' . $mime . '" src="' . $icon_url
    . '" />';
}

