<template>
  <div class="home">
    Home
    <br>
    <label @change="languageChange()" for="language">
      {{ this.language === 'en' ? 'Sprache: ' : 'Language: ' }}
        <select id="language" v-model="language">
          <option value="en">English</option>
          <option value="de">Deutsch</option>
        </select>
      </label>
    <WriteComponentVue :sentence="generateSequence()" />
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
      return Array.from({ length: 2 }, this.getRandomWord).join(' ');
    },
    getRandomWord() {
      return this.words[Math.floor(Math.random() * this.words.length)];
    },
  },
});
</script>
