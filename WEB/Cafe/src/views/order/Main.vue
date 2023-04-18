<template>
  <div>
    <div class="main-container">

      <div>
        <router-link to="/orders/register">
          <b-button class="order-button" variant="outline-dark"
            >주문하기</b-button>
        </router-link>
      </div>

      <div>
        <router-link to="/orders/list">
          <b-button class="order-button" variant="outline-dark"
            >주문 내역 조회하기</b-button
          >
        </router-link>
      </div>

      <div class="icon-wrapper">
        <span class="material-symbols-outlined"> local_cafe </span>
      </div>
    </div>


  </div>
</template>


<script>
export default {
  components: {},

  async created() {
    this.$store.commit("SET_TITLE", "주문 페이지");
  },
};
</script>


<style scoped>
.main-container {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}
.main-container > div {
  text-align: center;
  margin-top: 30px;
}

.icon-wrapper > span {
  font-size: 80px;
}

.order-button {
  min-width: 180px;
}
</style>