<?php

/**
 * @file
 * ulf_internship_search.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ulf_internship_search_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'search_internships';
  $page->task = 'page';
  $page->admin_title = 'Search - Internships';
  $page->admin_description = '';
  $page->path = 'erhvervspraktik';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Erhvervspraktik',
    'name' => 'main-menu',
    'weight' => '1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_search_internships__panel_context_53ef60d7-27ce-4bd1-aa44-6737cd7bc12a';
  $handler->task = 'page';
  $handler->subtask = 'search_internships';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '628079a0-513c-4ad1-965b-dc9dd22943cc';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_search_internships__panel_context_53ef60d7-27ce-4bd1-aa44-6737cd7bc12a';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-dfa56415-9735-4149-b13c-fecff6fecb10';
  $pane->panel = 'middle';
  $pane->type = 'search_box';
  $pane->subtype = 'search_box';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'text' => '',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
    'search_node' => array(
      'id' => '1581322896',
      'server' => 'search_node',
      'index' => 'internships',
      'options' => array(
        'match_type' => 'best_fields',
        'match_operator' => 'or',
        'cache_expire' => '300',
        'size' => '14',
        'initial_query_enable' => 1,
        'initial_query_text' => '',
        'fields' => array(
          'author:field_profile_name' => 'author:field_profile_name',
          'title' => 'title',
          'author' => 0,
          'internship:field_business_type' => 0,
          'author:field_lokation' => 0,
          'author:field_tilbudsforpligtelser' => 0,
          'author:url' => 0,
          'changed' => 0,
          'created' => 0,
          'field_full_description:value' => 0,
          'field_image:file' => 0,
          'field_location' => 0,
          'field_price' => 0,
          'field_subjects_primary_school' => 0,
          'field_target_group_sub' => 0,
          'nid' => 0,
          'search_api_language' => 0,
          'type' => 0,
          'url' => 0,
        ),
        'filters' => array(
          'taxonomy' => array(
            'internship:field_business_type' => 'internship:field_business_type',
            'author:field_lokation' => 'author:field_lokation',
            'author:field_tilbudsforpligtelser' => 0,
            'field_subjects_primary_school' => 0,
            'field_target_group_sub' => 0,
          ),
          'boolean' => array(
            'author:field_garantipartner' => 'author:field_garantipartner',
          ),
        ),
      ),
      'filters' => array(
        'type' => array(
          'internship:field_business_type' => 'and',
          'author:field_lokation' => 'and',
          'author:field_tilbudsforpligtelser' => 'and',
          'field_subjects_primary_school' => 'or',
          'field_target_group_sub' => 'or',
        ),
      ),
      'sorting' => array(
        'field' => 'changed',
        'order' => 'desc',
      ),
      'dates' => array(
        'fields' => array(),
      ),
      'intervals' => array(
        'fields' => array(
          'author' => 0,
          'internship:field_business_type' => 0,
          'author:field_lokation' => 0,
          'author:field_profile_name' => 0,
          'author:field_tilbudsforpligtelser' => 0,
          'author:url' => 0,
          'changed' => 0,
          'created' => 0,
          'field_full_description:value' => 0,
          'field_image:file' => 0,
          'field_location' => 0,
          'field_price' => 0,
          'field_subjects_primary_school' => 0,
          'field_target_group_sub' => 0,
          'nid' => 0,
          'search_api_language' => 0,
          'title' => 0,
          'type' => 0,
          'url' => 0,
        ),
      ),
      'forces' => array(
        'field' => '_none_',
        'selected' => array(),
      ),
      'highlight' => array(
        'fields' => array(
          'author' => 0,
          'internship:field_business_type' => 0,
          'author:field_lokation' => 0,
          'author:field_profile_name' => 0,
          'author:field_tilbudsforpligtelser' => 0,
          'author:url' => 0,
          'changed' => 0,
          'created' => 0,
          'field_full_description:value' => 0,
          'field_image:file' => 0,
          'field_location' => 0,
          'field_price' => 0,
          'field_subjects_primary_school' => 0,
          'field_target_group_sub' => 0,
          'nid' => 0,
          'search_api_language' => 0,
          'title' => 0,
          'type' => 0,
          'url' => 0,
        ),
      ),
      'templates' => array(
        'box' => 'sites/ungegarantien.dk/themes/ulf_hjoerring/templates/search/angular/search-internship.html',
        'result' => 'sites/ungegarantien.dk/themes/ulf_hjoerring/templates/search/angular/results-internship.html',
        'pager' => 'profiles/ulf/themes/ulf_default/templates/search/angular/pager.html',
        'popup' => 'profiles/ulf/themes/ulf_default/templates/search/angular/popup-course.html',
      ),
      'autocomplete' => array(
        'index' => 'internships',
        'field' => '_none_',
        'minChars' => '3',
        'size' => '1',
      ),
      'map' => array(
        'points' => '10000',
        'markers' => '/profiles/ulf/themes/ulf_default/images/leaflet/',
      ),
    ),
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'dfa56415-9735-4149-b13c-fecff6fecb10';
  $display->content['new-dfa56415-9735-4149-b13c-fecff6fecb10'] = $pane;
  $display->panels['middle'][0] = 'new-dfa56415-9735-4149-b13c-fecff6fecb10';
  $pane = new stdClass();
  $pane->pid = 'new-485b89b0-43a3-4592-8e8e-d0f5160a9288';
  $pane->panel = 'middle';
  $pane->type = 'search_result';
  $pane->subtype = 'search_result';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '485b89b0-43a3-4592-8e8e-d0f5160a9288';
  $display->content['new-485b89b0-43a3-4592-8e8e-d0f5160a9288'] = $pane;
  $display->panels['middle'][1] = 'new-485b89b0-43a3-4592-8e8e-d0f5160a9288';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  return $page;
}
