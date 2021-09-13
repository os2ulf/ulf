<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="<?php print $classes; ?>">
  <?php //print render($content); ?>
  <?php if (isset($content['field_paragraph_button'])): ?>
  <a href="<?php print $content['field_paragraph_button']['#items'][0]['url']; ?>"<?php if (isset($content['field_paragraph_button']['#items'][0]['attributes']['target'])) { print ' target="' . $content['field_paragraph_button']['#items'][0]['attributes']['target'] . '"'; } ?>>
  <?php endif; ?>

    <div class="image-with-link__wrapper">
      <?php if (isset($content['field_paragraph_image'])): ?>
        <div class="image-with-link__image">
          <?php print render($content['field_paragraph_image']); ?>
        </div>
      <?php endif; ?>

      <?php if (isset($content['field_image_with_link_title'])): ?>
        <div class="image-with-link__content" <?php print $attributes; ?>>
          <h2><?php print nl2br($content['field_image_with_link_title']['#items'][0]['value']); ?></h2>
        </div>
      <?php elseif (isset($content['field_paragraph_title'])): ?>
        <div class="image-with-link__content" <?php print $attributes; ?>>
          <?php print render($content['field_paragraph_title']); ?>
        </div>
      <?php endif; ?>
    </div>

  <?php if (isset($content['field_paragraph_button'])): ?>
  </a>
  <?php endif; ?>
</div>
