import Vue from 'vue'
import VueRouter from 'vue-router'

import Main from "../views/Main.vue"

import AdminMenuMain from "../views/admin-menu/Main.vue"
import AdminMenuList from "../views/admin-menu/List.vue"
import AdminMenuDetail from "../views/admin-menu/Detail.vue"
import AdminMenuRegister from "../views/admin-menu/Register.vue"

import OrderMain from "../views/order/Main.vue"
import OrderList from "../views/order/List.vue"
import OrderDetail from "../views/order/Detail.vue"
import OrderRegister from "../views/order/Register.vue"

Vue.use(VueRouter)

const routes = [
  // Main
  {
    path: '/',
    component: Main
  },
  //admin
  { // admin 메인 페이지
    path: '/admin/home',
    component: AdminMenuMain
  },
  { // 메뉴 리스트
    path: '/admin/menus',
    component: AdminMenuList
  },
  { // 메뉴 등록
    path: '/admin/menus/register',
    component: AdminMenuRegister
  },
  { // 메뉴 상세 보기
    path: '/admin/menus/:id',
    component: AdminMenuDetail
  },
  { // 메뉴 수정 
    path: '/admin/menus/register/:id',
    component: AdminMenuRegister
  },

  // Order
  {
    // 메뉴 리스트
    path: '/orders/home',
    component: OrderMain
  },
  {
    // 메뉴 리스트
    path: '/orders/list',
    component: OrderList
  },
  {
    path: '/orders/register',
    component: OrderRegister
  },
  {
    path: '/orders/register/:id',
    component: OrderRegister
  },
  {
    path: '/orders/list/:id',
    component: OrderDetail
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
