<template>
    <div @keydown="() => null" @click="this.activateInput()">
      <ul>
          <li>
            {{ Math.floor(timer) }}
            {{ this.language === 'de' ? 'Sekunden' : 'seconds' }}
          </li>
          <li>
            {{ Math.floor(cpm) }}
            {{ this.language === 'de' ? 'Zeichen pro Minute' : 'charakters per minute' }}
          </li>
          <li>
            {{ Math.floor(wpm) }}
            {{ this.language === 'de' ? 'Wörter pro Minute' : 'words per minute' }}
          </li>
          <li v-if="done">
            Fertig
          </li>
          <li>
            <button @click="this.$router.go()">{{ language === 'de'
            ? 'Nochmal versuchen'
            : 'Try again' }}</button>
          </li>
        </ul>
    </div>
    <p @keydown="() => null" @click="this.activateInput()"
      class="result" v-html="makeText()"></p>
    <p class="code" v-if="code !== ''">
      Du hast es über {{ minWpm }} Wpm geschafft! Das ist dein code: {{ code }}</p>
      <br>
      <p class="hint">{{ language === 'de'
      ? 'Wenn du nicht schreiben kannst, clicke auf den Text oder auf "Nochmal versuchen"'
      : 'If you can\'t type, try clicking the text or the "Try again" button' }}</p>
      <p v-if="this.toSlow">Du warst leider zu langsam, bitte versuche es noch einmal</p>
    <!-- hidden input this is used so we won't need keylisteners -->
    <label style="opacity: 0; width: 0; height: 0;" for="input">
      <input  @input="inputHandler()"
      style="width: 0; height: 0;" id="input" ref="input" type="text" v-model="input">
    </label>
</template>

<script>import { defineComponent } from 'vue';

export default defineComponent({
  props: ['sentence'],
  data() {
    return {
      input: '',
      timer: 0,
      timerBegun: false,
      begin: null,
      end: null,
      minWpm: 10,
      wpm: 0,
      cpm: 0,
      done: false,
      code: '',
      toSlow: false,
    };
  },
  mounted() {
    this.activateInput();
    this.fetchTimer();
  },
  methods: {
    activateInput() {
      if (this.done) return; // dont activate the input again
      this.$refs.input.focus();
    },
    colorize() {
      return this.input.split('')
        .map((e, i) => `<span style="color: ${this.sentence[i] === e ? 'green' : 'red'};">${e}</span>`)
        .join('');
    },
    makeText() {
      return `${this.colorize()}<span style="color: gray;">${this.sentence.substring(this.input.length)}</span>`;
    },
    fetchTimer() {
      if (this.done) return;
      setTimeout(() => {
        this.fetchTimer();
      }, 100);
      if (!this.timerBegun) return;
      this.end = Date.now();
      this.timer = (this.end - this.begin) / 1000;
      this.cpm = this.input.length / (this.timer / 60);
      this.wpm = this.cpm / 5;
    },
    inputHandler() {
      if (!this.timerBegun) {
        this.begin = Date.now();
        this.timerBegun = !this.timerBegun;
      }
      this.end = Date.now();
      this.timer = (this.end - this.begin) / 1000;
      this.cpm = this.input.length / (this.timer / 60);
      this.wpm = this.cpm / 6;
      if (this.input === this.sentence) {
        this.success();
      }
    },
    success() {
      this.done = true;
      this.$refs.input.blur();
      if (this.wpm > this.minWpm) {
        this.genCode();
      } else {
        this.toSlow = true;
      }
    },
    genCode() {
      const headers = new Headers();
      headers.append(
        'Authorization',
        `Basic ${btoa(`${this.$store.state.username}:${this.$store.state.password}`)}`,
      );
      fetch(`${this.$store.state.API_URL}/generateToken`, {
        method: 'GET',
        headers,
      })
        .then((r) => r.text()
          .then((t) => {
            this.code = t;
          }));
    },
  },
  computed: {
    language() {
      return this.$store.state.language;
    },
  },
});

</script>

<style lang="scss">

ul {
  list-style-type: none;
  display: flex;
  flex-direction: row;
  justify-content: left;
  padding: 0;
  margin: 0;
  width: 100%;
  li {
    display: block;
    padding: 8px;
  }
}

.hint {
  color: black;
  font-size: 10px;
}

</style>
