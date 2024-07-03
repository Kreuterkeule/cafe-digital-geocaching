<template>
  <router-view/>
</template>

<style lang="scss">

/* roboto-regular - latin */
@font-face {
  font-display: swap;
  font-family: 'Roboto';
  font-style: normal;
  font-weight: 400;
  src: url('@/assets/fonts/roboto-v30-latin-regular.woff2') format('woff2');
}

/* roboto-italic - latin */
@font-face {
  font-display: swap;
  font-family: 'Roboto';
  font-style: italic;
  font-weight: 400;
  src: url('@/assets/fonts/roboto-v30-latin-italic.woff2') format('woff2');
}

* {
  padding: 0;
  margin: 0;
  font-family: 'Roboto';
}

</style>
