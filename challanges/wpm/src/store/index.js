import VuexPersistence from 'vuex-persist';
import { createStore } from 'vuex';

const vuexLocal = new VuexPersistence({
  key: 'vuex',
  storage: window.localStorage,
  reducer: (state) => state,
});

export default createStore({
  state: {
    API_URL: 'http://localhost:8080',
    language: 'de',
    username: 'admin',
    password: '1234',
  },
  getters: {
  },
  mutations: {
    language(state, lang) {
      state.language = lang;
    },
  },
  actions: {
  },
  modules: {
  },
  plugins: [vuexLocal.plugin],
});
