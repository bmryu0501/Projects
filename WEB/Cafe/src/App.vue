<template>
  <div id="app">
    <!-- header -->
    <header>
      <!-- vuex로 변경 -->
      <h2>{{$store.state.title}}</h2>
    </header>

    <router-view></router-view>

    <!-- footer -->
    <footer>
      <div>All right reserved</div>
      <router-link to="/admin/home">관리자 페이지(메뉴)</router-link>
      <br/>
      <router-link to="/orders/home">메인 페이지(주문)</router-link>
    </footer>
  </div>
</template>

<script>

export default ({

})
</script>

<style>
header,
footer {
  border-top: 2px solid grey;
  border-bottom: 2px solid grey;
}

#app {
  display: flex;
  flex-direction: column;
  min-height: 100vh;
}

#app > header {
  /* flex:1; */
  text-align: center;
}

#app > div {
  /* header랑 footer만 제외하고 늘어난다 */
  flex: 1;
}

#app > footer {
  text-align: center;
  /* flex: 1; */
}

.page-loading {
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
}
</style>