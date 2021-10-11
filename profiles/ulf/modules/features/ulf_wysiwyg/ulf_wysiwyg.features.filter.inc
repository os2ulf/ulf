<?php

/**
 * @file
 * ulf_wysiwyg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function ulf_wysiwyg_filter_default_formats() {
  $formats = array();

  // Exported format: Editor.
  $formats['editor'] = array(
    'format' => 'editor',
    'name' => 'Editor',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_url' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_html' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <u> <strong> <blockquote> <ul> <ol> <li> <p> <br> <h2> <h3><sub><sup>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -47,
        'status' => 1,
        'settings' => array(),
      ),
      'strip_emojis' => array(
        'weight' => -46,
        'status' => 1,
        'settings' => array(),
      ),
      'spamspan' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'spamspan_at' => ' [at] ',
          'spamspan_use_graphic' => 0,
          'spamspan_dot_enable' => 1,
          'spamspan_dot' => ' [dot] ',
          'spamspan_use_form' => 0,
          'spamspan_form_pattern' => '<a href="%url?goto=%email">%displaytext</a>',
          'spamspan_form_default_url' => 'contact',
          'spamspan_form_default_displaytext' => 'contact form',
        ),
      ),
    ),
  );

  // Exported format: Full html.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full html',
    'cache' => 0,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'spamspan' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'spamspan_at' => ' [at] ',
          'spamspan_use_graphic' => 0,
          'spamspan_dot_enable' => 1,
          'spamspan_dot' => ' [dot] ',
          'spamspan_use_form' => 0,
          'spamspan_form_pattern' => '<a href="%url?goto=%email">%displaytext</a>',
          'spamspan_form_default_url' => 'contact',
          'spamspan_form_default_displaytext' => 'contact form',
        ),
      ),
      'filter_tokens' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Plain text.
  $formats['plain_text'] = array(
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => 10,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'spamspan' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'spamspan_at' => ' [at] ',
          'spamspan_use_graphic' => 0,
          'spamspan_dot_enable' => 1,
          'spamspan_dot' => ' [dot] ',
          'spamspan_use_form' => 0,
          'spamspan_form_pattern' => '<a href="%url?goto=%email">%displaytext</a>',
          'spamspan_form_default_url' => 'contact',
          'spamspan_form_default_displaytext' => 'contact form',
        ),
      ),
      'filter_url' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
