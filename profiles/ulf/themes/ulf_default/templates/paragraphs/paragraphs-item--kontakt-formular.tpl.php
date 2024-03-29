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
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($content['field_contact_form_title'][0])): ?>
    <h2 class="contact-form__title"><?php print $content['field_contact_form_title'][0]['#markup']; ?></h2>
  <?php endif; ?>
  <?php if (isset($content['field_contact_form_description'][0])): ?>
    <div class="contact-form__description">
      <?php print $content['field_contact_form_description'][0]['#markup']; ?>
    </div>
  <?php endif; ?>
  <?php if (isset($content['field_kontakt_formular'][0])): ?>
    <div class="contact-form">
      <?php print render($content['field_kontakt_formular']); ?>
    </div>
  <?php endif; ?>
</div>
