<?php
/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
<div class="layout-profile">
  <div class="layout-inner">
    <div class="layout-element-alpha">
      <div class="layout-element-alpha-inner">
        <div class="content">
          <div class="content--image">
            <h1 class="field--title is-profile">
              <?php print render($user_profile['field_profile_name']); ?>
            </h1>
            <?php print render($user_profile['field_image']); ?>
          </div>
          <div class="content--main">
            <h2 class="block--field-label"><?php print t('Presentation');?></h2>
            <?php print render($user_profile['field_profile_description']); ?>
            <?php if (isset($user_profile['field_profile_educat_profi'])) : ?>
              <h2 class="block--field-label"><?php print t('Educational profile');?></h2>
              <?php print render($user_profile['field_profile_educat_profi']); ?>
            <?php endif; ?>
            <?php print render($user_profile['field_profile_entry']); ?>
            <?php print render($user_profile['field_video']); ?>
            <?php print render($user_profile['field_profile_contact']); ?>
            <?php print render($user_profile['field_further_information']); ?>
            <div class="block--pdf">
              <a class="block--pdf-link" target="_blank" href="/printpdf/user/<?php print $elements['#account']->uid; ?>"><?php print t('Print this offer as pdf')?></a>
            </div>
          </div>
          <div class="content--meta">
            <?php if (isset($user_profile['field_profile_logo'])) :?>
              <div class="block">
                <div class="block--content">
                  <div class="block--field-logo">
                    <?php if (isset($field_profile_home_page['0']['url'] )) :?>
                      <a href="<?php print $field_profile_home_page['0']['url'];?>" target="_blank">
                        <?php print render($user_profile['field_profile_logo']); ?>
                      </a>
                    <?php else : ?>
                      <?php print render($user_profile['field_profile_logo']); ?>
                    <?php endif; ?>
                  </div>
                </div>
              </div>
            <?php endif; ?>
            <div class="block--dark">
              <h2 class="block--header">
                <?php print t('Organizer');?>
              </h2>
              <div class="block--content">
                <div class="block--field-label"><?php print render($user_profile['field_profile_name']); ?></div>
                <?php if (isset($location)) : ?>
                  <div class="block--field-text"><?php print $location['name']; ?></div>
                  <div class="block--field-text"><?php print $location['street']; ?></div>
                  <div class="block--field-text"><?php print $location['postal_code']; ?> <?php print $location['city']; ?></div>
                  </br>
                <?php endif;?>
                <?php if (isset($user_profile['field_profile_phone'])) : ?>
                  <div class="block--field-text"><?php print t('Phone')?> <?php print render($user_profile['field_profile_phone']); ?></div>
                <?php endif;?>
                <div class="block--field-text"><?php print render($user_profile['field_profile_mail']); ?></div>
                <div class="block--field-text"><?php print render($user_profile['field_profile_home_page']); ?></div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <?php if (variable_get('ulf_users_admin_show_authored')) : ?>
      <div class="layout-element-beta">
        <div class="layout-element-beta-inner">
          <?php if (isset($field_profile_name)) :?>
            <h2 class="layout--element-header"><?php print t('Offers from') . ' ' . $field_profile_name['0']['value'] ;?></h2>
          <?php endif;?>
          <?php print $content_by_user_daycare; ?>
          <?php print $content_by_user_school; ?>
          <?php print $content_by_user_youth; ?>
          <?php print $content_by_user_courses; ?>
          <?php print $content_by_user_news; ?>
        </div>
      </div>
    <?php endif;?>
  </div>
</div>
<?php hide($user_profile['summary']); ?>
<?php hide($user_profile['mimemail']); ?>
<?php print render($user_profile); ?>
