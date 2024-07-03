<template>
  <div class="header">
    <div class="image-wrapper">
      <img src="@/assets/logo_cafe-digital_header_weiss.webp" alt="">
    </div>
    <h1>Wpm Challenge</h1>
  </div>
  <div class="home-wrapper">
  <div class="home">
    <p v-if="language === 'de'">
      <!-- GERMAN -->
       Versuche den unten angezeigten Text so schnell wie möglich zu schreiben.
       Schreibst du schnell genug, bekommst du einen Einmalschlüssel für unseren Tresor
    </p>
    <p v-if="language === 'en'">
      <!-- ENGLISH -->
       Try to write out the text below as fast as possible.
       If you are fast enough, you'll get a onetime-key to open our vault.
    </p>
    <label @change="languageChange()" for="language">
      {{ this.language === 'en' ? 'Sprache: ' : 'Language: ' }}
        <select id="language" v-model="language">
          <option value="en">English</option>
          <option value="de">Deutsch</option>
        </select>
      </label>
    <WriteComponentVue :sentence="generateSequence()" />
  </div>
</div>
</template>

<script>
import WriteComponentVue from '@/components/WriteComponent.vue';
import { defineComponent } from 'vue';

export default defineComponent({
  name: 'HomeView',
  data() {
    return {
      words: [],
      wordlistUrl: 'words_de.txt',
      language: 'de',
      sentenceLength: 15,
    };
  },
  components: {
    WriteComponentVue,
  },
  mounted() {
    this.loadState();
    this.populateWords();
  },
  methods: {
    loadState() {
      this.language = this.$store.state.language;
    },
    populateWords() {
      fetch(`words_${this.$store.state.language}.txt`)
        .then((response) => {
          response.text()
            .then((text) => { this.words = text.split('\n'); });
        });
    },
    languageChange() {
      this.$store.commit('language', this.language);
      this.$router.go();
    },
    generateSequence() {
      return Array.from({ length: this.sentenceLength }, this.getRandomWord).join(' ');
    },
    getRandomWord() {
      return this.words[Math.floor(Math.random() * this.words.length)];
    },
  },
});
</script>

<style lang="scss">

.header {
  background-color: orange;
  width: 100%;
  height: fit-content;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  .image-wrapper {
    height: 64px;
    padding: 32px;
    img {
      height: 64px;
      width: auto;
    }
  }
  h1 {
    padding: 32px;
    color: white;
  }
}

.home-wrapper {
  padding: 24px;
  margin: 24px;
  background-color: #ddd;
}

</style>
