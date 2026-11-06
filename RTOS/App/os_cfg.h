#ifndef OS_CFG_H
#define OS_CFG_H

/* ---------------- Miscellaneous ---------------- */
#define OS_CFG_APP_HOOKS_EN                 0u
#define OS_CFG_ARG_CHK_EN                   0u
#define OS_CFG_CALLED_FROM_ISR_CHK_EN       0u
#define OS_CFG_DBG_EN                       0u
#define OS_CFG_TICK_EN                      1u
#define OS_CFG_DYN_TICK_EN                  0u
#define OS_CFG_INVALID_OS_CALLS_CHK_EN      0u
#define OS_CFG_OBJ_TYPE_CHK_EN              0u
#define OS_CFG_OBJ_CREATED_CHK_EN           0u
#define OS_CFG_TS_EN                        0u

#define OS_CFG_PRIO_MAX                     32u
#define OS_CFG_SCHED_LOCK_TIME_MEAS_EN      0u
#define OS_CFG_SCHED_ROUND_ROBIN_EN         0u
#define OS_CFG_STK_SIZE_MIN                 64u

/* ---------------- Event flags ---------------- */
#define OS_CFG_FLAG_EN                      0u
#define OS_CFG_FLAG_DEL_EN                  0u
#define OS_CFG_FLAG_MODE_CLR_EN             0u
#define OS_CFG_FLAG_PEND_ABORT_EN           0u

/* ---------------- Memory manager ---------------- */
#define OS_CFG_MEM_EN                       0u

/* ---------------- Mutexes ---------------- */
#define OS_CFG_MUTEX_EN                     0u
#define OS_CFG_MUTEX_DEL_EN                 0u
#define OS_CFG_MUTEX_PEND_ABORT_EN          0u

/* ---------------- Message queues ---------------- */
#define OS_CFG_Q_EN                         0u
#define OS_CFG_Q_DEL_EN                     0u
#define OS_CFG_Q_FLUSH_EN                   0u
#define OS_CFG_Q_PEND_ABORT_EN              0u

/* ---------------- Semaphores ---------------- */
#define OS_CFG_SEM_EN                       0u
#define OS_CFG_SEM_DEL_EN                   0u
#define OS_CFG_SEM_PEND_ABORT_EN            0u
#define OS_CFG_SEM_SET_EN                   0u

/* ---------------- Task management ---------------- */
#define OS_CFG_STAT_TASK_EN                 0u
#define OS_CFG_STAT_TASK_STK_CHK_EN         0u
#define OS_CFG_TASK_CHANGE_PRIO_EN          0u
#define OS_CFG_TASK_DEL_EN                  0u
#define OS_CFG_TASK_IDLE_EN                 1u
#define OS_CFG_TASK_PROFILE_EN              0u
#define OS_CFG_TASK_Q_EN                    0u
#define OS_CFG_TASK_Q_PEND_ABORT_EN         0u
#define OS_CFG_TASK_REG_TBL_SIZE            0u
#define OS_CFG_TASK_STK_REDZONE_EN          0u
#define OS_CFG_TASK_STK_REDZONE_DEPTH       8u
#define OS_CFG_TASK_SEM_PEND_ABORT_EN       0u
#define OS_CFG_TASK_SUSPEND_EN              0u

/* ---------------- Task local storage ---------------- */
#define OS_CFG_TLS_TBL_SIZE                 0u

/* ---------------- Time management ---------------- */
#define OS_CFG_TIME_DLY_HMSM_EN             1u
#define OS_CFG_TIME_DLY_RESUME_EN           0u

/* ---------------- Timer management ---------------- */
#define OS_CFG_TMR_EN                       0u
#define OS_CFG_TMR_DEL_EN                   0u

/* ---------------- Trace ---------------- */
#define OS_CFG_TRACE_EN                     0u
#define OS_CFG_TRACE_API_ENTER_EN           0u
#define OS_CFG_TRACE_API_EXIT_EN            0u

#endif
