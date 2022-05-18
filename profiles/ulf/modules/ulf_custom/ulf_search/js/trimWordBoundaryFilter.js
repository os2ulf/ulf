/**
 * @file
 * Create filter that pads a number with zero's.
 *
 * @TODO: Move this back to the main angular library, when it's perfect.
 */
angular.module('searchResultApp').filter('trimWordBoundary', function () {
  "use strict";

  return function (str, len) {
    // Ensure that the string is defined and it's larger than required length.
    if (str === undefined) {
      return;
    }

    // Redefine variable if str is an array
    if (str[0]['value'] !== undefined) {
      str = str[0]['value'];
    }

    // Clean out headlines.
    str = str.replace(/(<h\d>).+(<\/h\d>)/gi, '');

    // Clean out HTML.
    str = str.replace(/(<([^>]+)>)/gi, '');

    if (str.length === 0 || str.length < len) {
      return str;
    }

    // Trim string to word boundery.
    var trimmedString = str.substr(0, len);
    str = trimmedString.substr(0, Math.min(trimmedString.length, trimmedString.lastIndexOf(" ")));

    return str + '...';
  };
});
