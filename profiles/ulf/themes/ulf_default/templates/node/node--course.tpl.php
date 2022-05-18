<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<div class="layout-node">
  <div class="layout-element-alpha">
    <div class="layout-element-alpha-inner">
      <?php if ($display_submitted): ?>
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>
      <div class="content is-<?php print $group_type; ?>">
        <div class="content--image">

          <?php if (isset($ribbon_message)) : ?>
            <div class="ribbon-wrapper left is-content">
              <div class="ribbon is-content">
                <div class="ribbon--course is-content"><?php print $ribbon_message; ?></div>
              </div>
            </div>
          <?php else: ?>
            <?php if (isset($field_free['0']) && $field_free['0']['value'] == 1) : ?>
              <div class="ribbon-wrapper left is-content">
                <div class="ribbon is-content">
                  <div class="ribbon--course is-content"><?php print t('Free'); ?></div>
                </div>
              </div>
            <?php endif;?>
          <?php endif;?>

          <h1 class="field--title is-<?php print $group_type; ?>"><?php print render($title); ?></h1>
          <?php print render($content['field_image']); ?>
        </div>
        <div class="content--main">
          <?php print render($content['field_full_description']); ?>

          <div class="course-activity">
            <?php print render($content['field_activities']); ?>
            <?php print render($content['field_background_knowledge']); ?>
            <?php print render($content['field_post_work']); ?>
            <?php print render($content['field_material_suggestions']); ?>
            <?php print render($content['field_purpose']); ?>
          </div>

          <?php print render($content['field_video']); ?>
          <?php if ($field_place || $field_map_placement['und']['0']['value'] == 'alternative' || $field_map_placement['und']['0']['value'] == 'provider'): ?>
            <div class="field--collection-wrapper">
              <div class="field--collection-label"><?php print t('Place');?></div>
              <div class="field--collection-content">
                <div class="field--collection-item">
                  <?php if ($field_map_placement['und']['0']['value'] == 'alternative' ) : ?>
                    <?php if (!empty($location['name'])) : ?>
                      <div><?php print $location['name'] ?></div>
                    <?php endif; ?>
                    <?php if (!empty($location['street'])) : ?>
                      <div><?php print $location['street'] ?></div>
                    <?php endif; ?>
                    <?php if (!empty($location['additional'])) : ?>
                      <div><?php print $location['additional'] ?></div>
                    <?php endif; ?>
                    <?php if (!empty($location['postal_code'])) : ?>
                      <span><?php print $location['postal_code'] ?></span>
                    <?php endif; ?>
                    <?php if (!empty($location['city'])) : ?>
                      <span><?php print $location['city'] ?></span>
                    <?php endif; ?>
                  <?php endif; ?>
                  <?php if ($field_map_placement['und']['0']['value'] == 'provider'): ?>
                    <div><?php print $profile_name; ?></div>
                    <div><?php print $profile_address; ?></div>
                    <div><?php print $profile_postal_code; ?> <?php print $profile_city; ?></div>
                  <?php endif; ?>
                  <?php if (!empty($field_place)): ?>
                    <p>
                      <?php print render($content['field_place']); ?>
                    </p>
                  <?php endif; ?>
                </div>
              </div>
            </div>
          <?php endif; ?>
          <?php print render($content['field_educational_material']); ?>
          <?php print render($content['field_inspirational_material']); ?>
          <?php if ($field_last_signup_date || $field_signup_link || $field_signup_email || $field_signup_phone || $field_signup_description ) : ?>
            <div class="field--collection-wrapper">
              <div class="field--collection-label"><?php print t('Signup');?></div>
              <div class="field--collection-content">
                <div class="field--collection-item">
                  <div class="field--collection-item-inner">
                    <div class="field--collection-description">
                      <?php print render($content['field_signup_description']); ?>
                      <?php print render($content['field_signup_link']); ?>
                      <?php print render($content['field_signup_email']); ?>
                      <?php print render($content['field_signup_phone']); ?>
                      <?php print render($content['field_last_signup_date']); ?>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          <?php endif;?>

          <?php if (isset($content['field_pretix_date'])): ?>
            <?php print render($content['field_pretix_date']); ?>
          <?php endif; ?>

          <?php if(module_exists('ulf_pretix')) : ?>
            <?php if(isset($pretix_widget)) : ?>
              <div class="pretix-widget-wrapper">
                <div class="field--collection-label"><?php print t('Signup'); ?></div>
                <?php print $pretix_widget['stylesheet']; ?>
                <?php print $pretix_widget['javascript']; ?>
                <?php print $pretix_widget['widget']; ?>
                <?php print $pretix_widget['noscript']; ?>
              </div>
            <?php endif;?>
          <?php endif;?>
          <div class="block--pdf">
            <a class="block--pdf-link" target="_blank" href="/printpdf/<?php print $node->nid; ?>"><?php print t('Save this offer as pdf'); ?></a>
          </div>
        </div>
        <div class="content--meta">
          <div class="block--light">
            <h2 class="block--header">
              <?php print t('Practical information'); ?>
            </h2>
            <div class="block--content">
              <div class="block--field-wrapper">
                <div class="block--field-label"><?php print t('Provider');?></div>
                <p><a href="/user/<?php print $uid; ?>"><?php print $profile_name; ?></a></p>
              </div>
              <div class="block--field-wrapper is-inline">
                <?php print render($content['field_offer_type']); ?>
                <?php if (!empty($view__target_group_sub)) : ?>
                  <div class="block--field-label"><?php print t('Target group');?></div>
                  <div class="block--field-text"><?php print render($view__target_group_sub); ?></div>
                <?php endif;?>
              </div>
              <?php /* If any of the fields in this wrapper contain data */ ?>
              <?php print render($content['field_count']); ?>
              <?php print render($content['field_count_description']); ?>
              <?php if ($field_duration || $field_period_full_year['0']['value'] == 0 || $field_collection_price || (isset($field_free['0']) && $field_free['0']['value'] == 1) || $field_price_description || $field_duration_description || $field_period_info ) : ?>
                <div class="block--field-wrapper">
                  <?php if ($field_period_full_year['0']['value'] == 0 ) : ?>
                    <?php print render($content['field_period']); ?>
                  <?php else : ?>
                    <div class="block--field-label"><?php print t('Periode');?></div>
                    <div class="block--field-text"><?php print t('All year');?></div>
                  <?php endif;?>
                  <?php print render($content['field_period_info']); ?>
                  <?php if ($field_duration || $field_duration_description) : ?>
                    <div class="block--field-label"><?php print t('Duration');?></div>
                    <?php if ($field_duration) : ?>
                      <div class="block--field-text"><?php print $stripped_duration; ?><?php print render($content['field_duration_unit']); ?></div>
                    <?php endif; ?>
                    <?php if ($field_duration_description) : ?>
                      <div class="block--field-text"><?php print render($content['field_duration_description']); ?></div>
                    <?php endif; ?>
                  <?php endif;?>
                  <?php /* 'und' part of field_free is used for pdf displays  */ ?>
                  <?php if ((isset($field_free['0']) && $field_free['0']['value'] == 0 ) || (isset($field_free['und']) && $field_free['und']['0'] && $field_free['und']['0']['value'] == 0 )) : ?>
                    <div class="block--field-label"><?php print t('Price');?></div>
                    <?php print render($content['field_collection_price']); ?>
                  <?php else : ?>
                    <div class="block--field-label"><?php print t('This course is free.');?></div>
                  <?php endif;?>
                  <?php if ($field_price_description) : ?>
                    <div class="block--field-text"><?php print render($content['field_price_description']); ?></div>
                  <?php endif; ?>
                </div>
              <?php endif;?>
              <?php /* If any of the fields in this wrapper contain data */ ?>
              <?php if ($field_subject) : ?>
                <div class="block--field-wrapper">
                  <?php print render($content['field_subject']); ?>
                </div>
              <?php endif;?>
              <?php if ($field_educational_goals || $field_subjects_primary_school || $field_subjects_youth) : ?>
                <div class="block--field-wrapper">
                  <?php print render($content['field_educational_goals']); ?>
                  <?php print render($content['field_subjects_primary_school']); ?>
                  <?php print render($content['field_subjects_youth']); ?>
                </div>
              <?php endif; ?>
              <?php if ($field_facilities || $field_facilities_info) : ?>
                <div class="block--field-wrapper">
                  <?php print render($content['field_facilities']); ?>
                  <?php print render($content['field_facilities_info']); ?>
                </div>
              <?php endif; ?>
            </div>

            <?php if (module_exists('ulf_world_targets') && isset($world_targets)) : ?>
              <div class="block--field-wrapper">
                <?php print $world_targets; ?>
                <?php if (isset($node->field_world_targets_description['und'])): ?>
                  <div class="world-targets-description">
                    <?php print $node->field_world_targets_description['und'][0]['value']; ?>
                  </div>
                <?php endif; ?>
              </div>
            <?php endif;?>

          </div>
          <?php if (module_exists('transportpulje_form') && $group_type != 'ungdomsuddannelse') : ?>
            <?php if (!empty($field_tpf_exclude)) : ?>
              <?php if ($field_tpf_exclude[LANGUAGE_NONE]['0']['value'] != 1) : ?>
                <div class="block--dark block--transport-request-link">
                  <h2 class="block--header">
                    <?php print t('Transport');?>
                  </h2>
                  <div class="block--content">
                    <div class="block--field-text"><?php print t('Create an application to request funding from the transport pool to attend this course'); ?></div>
                    <p>
                      <a target="_blank" href="/transport_application?course_id=<?php print $nid; ?>"><?php print t('Create transport application'); ?></a>
                    </p>
                  </div>
                </div>
              <?php endif; ?>
            <?php else : ?>
              <div class="block--dark block--transport-request-link">
                <h2 class="block--header">
                  <?php print t('Transport');?>
                </h2>
                <div class="block--content">
                  <div class="block--field-text"><?php print t('Create an application to request funding from the transport pool to attend this course'); ?></div>
                  <p>
                    <a target="_blank" href="/transport_application?course_id=<?php print $nid; ?>"><?php print t('Create transport application'); ?></a>
                  </p>
                </div>
              </div>
            <?php endif; ?>
          <?php endif; ?>
          <div class="block--dark">
            <h2 class="block--header">
              <?php print t('Contact organizer');?>
            </h2>
            <div class="block--content">
              <div class="block--field-label"><?php print $profile_name; ?></div>
              <div class="block--field-text"><?php print $profile_address; ?></div>
              <div class="block--field-text"><?php print $profile_postal_code; ?> <?php print $profile_city; ?></div>
              <br>
              <?php if (isset($profile_phone)) : ?>
                <div class="block--field-text">
                  <p>
                    <?php print t('Phone')?> <?php print $profile_phone; ?>
                  </p>
                </div>
              <?php endif; ?>
              <?php if ($field_message_form) : ?>
              <p>
                <button class="block--modal-link js-toggle-modal modal--open"><?php print t('Contact organizer'); ?></button>
              </p>
              <?php endif; ?>
              <p>
                <a href="/user/<?php print $uid ?>"><?php print t('View organizer profile'); ?></a>
              </p>
            </div>
          </div>
          <?php if ($field_message_form) : ?>
            <div class="block--light is-form">
            <div class="is-modal js-modal js-toggle-modal"></div>
              <div class="modal--wrapper js-modal-dialog">
                <div class="modal--close js-toggle-modal"><img src="/profiles/ulf/themes/ulf_default/images/close.svg"></div>
                <h2 class="block--header modal--header">
                  <?php print t('Send message to') . ' ' . $profile_name; ?>
                </h2>
                <?php if (isset($content['field_message_form'])): ?>
                <div class="block--content">
                  <?php print render($content['field_message_form']); ?>
                </div>
                <?php endif; ?>
              </div>
            </div>
          <?php endif; ?>
        </div>
      </div>
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['field_registration_form']);
      hide($content['field_target_group_sub']);
      hide($content['field_duration']);
      hide($content['field_duration_unit']);
      hide($content['field_period']);
      hide($content['field_collection_price']);
      hide($content['field_free']);
      hide($content['field_period_full_year']);
      hide($content['field_target_group']);
      hide($content['comments']);
      hide($content['links']); ?>
      <div style=""><?php print render($content); ?></div>
    </div>
  </div>
</div>
