<?php

/**
 * @file
 * Metatag integration for the Metatag Twitter Cards module.
 */

/**
 * Implements hook_metatag_bundled_config_alter().
 */
function metatag_twitter_cards_metatag_bundled_config_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'global':
        $config->config += array(
          'twitter:card' => array('value' => 'summary'),
          'twitter:title' => array('value' => '[current-page:title]'),
          'twitter:url' => array('value' => '[current-page:url:absolute]'),
        );
        break;

      case 'global:frontpage':
        $config->config += array(
          'twitter:description' => array('value' => '[site:slogan]'),
          'twitter:title' => array('value' => '[site:name]'),
          'twitter:url' => array('value' => '[site:url]'),
        );
        break;

      // On error pages point everything to the homepage.
      case 'global:403':
      case 'global:404':
        $config->config += array(
          'twitter:title' => array('value' => '[site:name]'),
          'twitter:url' => array('value' => '[site:url]'),
        );
        break;

      case 'node':
        $config->config += array(
          'twitter:description' => array('value' => '[node:summary]'),
          'twitter:title' => array('value' => '[node:title]'),
        );
        break;

      case 'taxonomy_term':
        $config->config += array(
          'twitter:description' => array('value' => '[term:description]'),
          'twitter:title' => array('value' => '[term:name]'),
        );
        break;

      case 'user':
        $config->config += array(
          'twitter:title' => array('value' => '[user:name]'),
        );
        if (variable_get('user_pictures')) {
          $config->config += array(
            'twitter:image' => array('value' => '[user:picture:url]'),
          );
        }
        break;
    }
  }
}

/**
 * Implements hook_metatag_info().
 */
function metatag_twitter_cards_metatag_info() {
  $info['groups']['twitter-cards'] = array(
    'label' => t('Twitter card'),
    'description' => t('A set of meta tags specially for controlling the summaries displayed when content is shared on <a href="!url">Twitter</a>.', array('!url' => 'https://twitter.com/')),
    'form' => array(
      '#weight' => 60,
    ),
  );

  // Twitter Cards meta tags stack after the Open Graph tags.
  $weight = 40;

  // Defaults used for all cards.
  $defaults = array(
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );

  $info['tags']['twitter:card'] = array(
    'label' => t('Twitter card type'),
    'description' => t('Notes:<ul><li>no other fields are required for a Summary card</li><li>Photo card requires the "image" field</li><li>Media player card requires the "title", "description", "media player URL", "media player width", "media player height" and "image" fields,</li><li>Summary Card with Large Image card requires the "Summary" field and the "image" field,</li><li>Gallery Card requires all the "Gallery Image" fields,</li><li>App Card requires the "iPhone app ID" field, the "iPad app ID" field and the "Google Play app ID" field,</li><li>Product Card requires the "description" field, the "image" field, the "Label 1" field, the "Data 1" field, the "Label 2" field and the "Data 2" field.</li></ul>'),
    'weight' => ++$weight,
    'form' => array(
      '#type' => 'select',
      '#options' => array(
        'summary' => t('Summary (default)'),
        'summary_large_image' => t('Summary with large image'),
        'player' => t('Media player'),
        'app' => t('App'),
      ),
      '#empty_option' => t('- None -'),
    ),
  ) + $defaults;
  $info['tags']['twitter:site'] = array(
    'label' => t('Site\'s Twitter account'),
    'description' => t('The @username for the website, which will be displayed in the Card\'s footer; must include the @ symbol.'),
    'context' => array('global'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'twitter',
    ),
  ) + $defaults;
  $info['tags']['twitter:site:id'] = array(
    'label' => t('Site\'s Twitter account ID'),
    'description' => t('The numerical Twitter account ID for the website, which will be displayed in the Card\'s footer.'),
    'context' => array('global'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $defaults;
  $info['tags']['twitter:creator'] = array(
    'label' => t('Creator\'s Twitter account'),
    'description' => t('The @username for the content creator / author for this page, including the @ symbol.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'twitter',
    ),
  ) + $defaults;
  $info['tags']['twitter:creator:id'] = array(
    'label' => t('Creator\'s Twitter account ID'),
    'description' => t('The numerical Twitter account ID for the content creator / author for this page.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $defaults;
  $info['tags']['twitter:title'] = array(
    'label' => t('Title'),
    'description' => t('The page\'s title, which should be concise; it will be truncated at 70 characters by Twitter. This field is required unless this the \'type\' field is set to "photo".'),
    'maxlength' => 70,
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['twitter:description'] = array(
    'label' => t('Description'),
    'description' => t('A description that concisely summarizes the content of the page, as appropriate for presentation within a Tweet. Do not re-use the title text as the description, or use this field to describe the general services provided by the website. The string will be truncated, by Twitter, at the word to 200 characters.'),
    'maxlength' => 200,
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['twitter:image'] = array(
    'label' => t('Image URL'),
    'description' => t('The URL to a unique image representing the content of the page. Do not use a generic image such as your website logo, author photo, or other image that spans multiple pages. Images larger than 120x120px will be resized and cropped square based on longest dimension. Images smaller than 60x60px will not be shown. If the \'type\' is set to <em>Photo</em> then the image must be at least 280x150px.'),
    'image' => TRUE,
    'weight' => ++$weight,
    'replaces' => array(
      'twitter:image:src',
    ),
    'devel_generate' => array(
      'type' => 'image',
    ),
  ) + $defaults;
  $info['tags']['twitter:image:alt'] = array(
    'label' => 'Image alternative text',
    'description' => 'The alternative text of the image being linked to. Limited to 420 characters.',
    'weight' => ++$weight,
    'dependencies' => array(
      array(
        'dependency' => 'twitter:image',
        'attribute' => 'value',
        'condition' => 'filled',
        'value' => TRUE,
      ),
    ),
  ) + $defaults;

  // 'player' cards.
  $player_defaults = array(
    'dependencies' => array(
      array(
        'dependency' => 'twitter:card',
        'attribute' => 'value',
        'condition' => 'value',
        'value' => 'player',
      ),
    ),
  ) + $defaults;
  $info['tags']['twitter:player'] = array(
    'label' => t('Media player URL'),
    'description' => t('The full URL for loading a media player. Required when using a <em>Media player</em> card.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'url',
    ),
  ) + $player_defaults;
  $info['tags']['twitter:player:width'] = array(
    'label' => t('Media player width'),
    'description' => t('The width of the media player iframe, in pixels. Required when using a <em>Media player</em> card.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $player_defaults;
  $info['tags']['twitter:player:height'] = array(
    'label' => t('Media player height'),
    'description' => t('The height of the media player iframe, in pixels. Required when using a <em>Media player</em> card.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $player_defaults;
  $info['tags']['twitter:player:stream'] = array(
    'label' => t('MP4 media stream URL'),
    'description' => t('The full URL for an MP4 video (h.264) or audio (AAC) stream, takes precidence over the other media player field.'),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'url',
    ),
  ) + $player_defaults;
  $info['tags']['twitter:player:stream:content_type'] = array(
    'label' => t('MP4 media stream MIME type'),
    'description' => t('The MIME type for the media contained in the stream URL, as defined by <a href="!url">RFC 4337</a>.', array('!url' => 'https://tools.ietf.org/rfc/rfc4337.txt')),
    'weight' => ++$weight,
    'devel_generate' => array(
      'maxlength' => 1,
    ),
  ) + $player_defaults;

  // 'app' cards.
  $info['tags']['twitter:app:country'] = array(
    'label' => t('App Store Country'),
    'description' => t('If your application is not available in the US App Store, you must set this value to the two-letter country code for the App Store that contains your application.'),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:name:iphone'] = array(
    'label' => t('iPhone app name'),
    'description' => t("The name of the iPhone app."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:id:iphone'] = array(
    'label' => t('iPhone app ID'),
    'description' => t("String value, should be the numeric representation of your iPhone app's ID in the App Store."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:url:iphone'] = array(
    'label' => t('iPhone app\'s custom URL scheme'),
    'description' => t('The iPhone app\'s custom URL scheme (must include "://" after the scheme name).'),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:name:ipad'] = array(
    'label' => t('iPad app name'),
    'description' => t("The name of the iPad app."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:id:ipad'] = array(
    'label' => t('iPad app ID'),
    'description' => t("String value, should be the numeric representation of your iPad app's ID in the App Store."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:url:ipad'] = array(
    'label' => t('iPad app\'s custom URL scheme'),
    'description' => t('The iPad app\'s custom URL scheme (must include "://" after the scheme name).'),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:name:googleplay'] = array(
    'label' => t('Google Play app name'),
    'description' => t("The name of the app in the Google Play app store."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:id:googleplay'] = array(
    'label' => t('Google Play app ID'),
    'description' => t("Your app ID in the Google Play Store (i.e. \"com.android.app\")."),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;
  $info['tags']['twitter:app:url:googleplay'] = array(
    'label' => t('Google Play app\'s custom URL scheme'),
    'description' => t('The Google Play app\'s custom URL scheme (must include "://" after the scheme name).'),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  ) + $defaults;

  return $info;
}
