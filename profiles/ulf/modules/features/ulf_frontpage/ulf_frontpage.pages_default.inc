<?php
/**
 * @file
 * ulf_frontpage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ulf_frontpage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front';
  $page->task = 'page';
  $page->admin_title = 'Front';
  $page->admin_description = '';
  $page->path = 'front';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'front';
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
  );
  $display = new panels_display();
  $display->layout = 'front_page';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'element_alfa' => NULL,
      'element_beta' => NULL,
      'alpha' => NULL,
      'beta' => NULL,
      'gamma' => NULL,
      'delta' => NULL,
      'epsilon' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '6fb78f12-9211-4cda-a334-37b51ae7d52f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-33e2aa56-be0c-4319-b6aa-7a981c91ae5b';
    $pane->panel = 'alpha';
    $pane->type = 'custom';
    $pane->subtype = 'group_daycare';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '33e2aa56-be0c-4319-b6aa-7a981c91ae5b';
    $display->content['new-33e2aa56-be0c-4319-b6aa-7a981c91ae5b'] = $pane;
    $display->panels['alpha'][0] = 'new-33e2aa56-be0c-4319-b6aa-7a981c91ae5b';
    $pane = new stdClass();
    $pane->pid = 'new-17f5878d-d206-4d03-a857-8a9285ac6898';
    $pane->panel = 'alpha';
    $pane->type = 'custom';
    $pane->subtype = 'group_school';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '17f5878d-d206-4d03-a857-8a9285ac6898';
    $display->content['new-17f5878d-d206-4d03-a857-8a9285ac6898'] = $pane;
    $display->panels['alpha'][1] = 'new-17f5878d-d206-4d03-a857-8a9285ac6898';
    $pane = new stdClass();
    $pane->pid = 'new-c173139a-96f9-4eee-b3bf-a13c7672eb08';
    $pane->panel = 'alpha';
    $pane->type = 'custom';
    $pane->subtype = 'group_youth';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'c173139a-96f9-4eee-b3bf-a13c7672eb08';
    $display->content['new-c173139a-96f9-4eee-b3bf-a13c7672eb08'] = $pane;
    $display->panels['alpha'][2] = 'new-c173139a-96f9-4eee-b3bf-a13c7672eb08';
    $pane = new stdClass();
    $pane->pid = 'new-b3960982-6674-462a-beed-faccfdf4ce89';
    $pane->panel = 'beta';
    $pane->type = 'views_panes';
    $pane->subtype = 'ulf_frontpage_promoted_courses-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b3960982-6674-462a-beed-faccfdf4ce89';
    $display->content['new-b3960982-6674-462a-beed-faccfdf4ce89'] = $pane;
    $display->panels['beta'][0] = 'new-b3960982-6674-462a-beed-faccfdf4ce89';
    $pane = new stdClass();
    $pane->pid = 'new-db2e483d-133c-4f55-b8da-0739c50c8739';
    $pane->panel = 'delta';
    $pane->type = 'custom';
    $pane->subtype = 'group_course';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'db2e483d-133c-4f55-b8da-0739c50c8739';
    $display->content['new-db2e483d-133c-4f55-b8da-0739c50c8739'] = $pane;
    $display->panels['delta'][0] = 'new-db2e483d-133c-4f55-b8da-0739c50c8739';
    $pane = new stdClass();
    $pane->pid = 'new-611d291a-2e89-467d-b6e0-dd791e94b058';
    $pane->panel = 'gamma';
    $pane->type = 'views_panes';
    $pane->subtype = 'ulf_frontpage_news-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '611d291a-2e89-467d-b6e0-dd791e94b058';
    $display->content['new-611d291a-2e89-467d-b6e0-dd791e94b058'] = $pane;
    $display->panels['gamma'][0] = 'new-611d291a-2e89-467d-b6e0-dd791e94b058';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front'] = $page;

  return $pages;

}