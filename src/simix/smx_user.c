#include "private.h"

/**
 * \brief Returns a host given its name.
 *
 * \param name The name of the host to get
 * \return The corresponding host
 */
smx_host_t SIMIX_req_host_get_by_name(const char *name)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_BY_NAME;
  req.host_get_by_name.name = name;
  SIMIX_request_push(&req);
  return req.host_get_by_name.result;
}

/**
 * \brief Returns the name of a host.
 *
 * \param host A SIMIX host
 * \return The name of this host
 */
const char* SIMIX_req_host_get_name(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_NAME;
  req.host_get_name.host = host;
  SIMIX_request_push(&req);
  return req.host_get_name.result;
}

/**
 * \brief Returns a dict of the properties assigned to a host.
 *
 * \param host A host
 * \return The properties of this host
 */
xbt_dict_t SIMIX_req_host_get_properties(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_PROPERTIES;
  req.host_get_properties.host = host;
  SIMIX_request_push(&req);
  return req.host_get_properties.result;
}

/**
 * \brief Returns the speed of the processor.
 *
 * The speed returned does not take into account the current load on the machine.
 * \param host A SIMIX host
 * \return The speed of this host (in Mflop/s)
 */
double SIMIX_req_host_get_speed(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_SPEED;
  req.host_get_speed.host = host;
  SIMIX_request_push(&req);
  return req.host_get_speed.result;
}

/**
 * \brief Returns the available speed of the processor.
 *
 * \return Speed currently available (in Mflop/s)
 */
double SIMIX_req_host_get_available_speed(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_AVAILABLE_SPEED;
  req.host_get_available_speed.host = host;
  SIMIX_request_push(&req);
  return req.host_get_available_speed.result;
}

/**
 * \brief Returns the state of a host.
 *
 * Two states are possible: 1 if the host is active or 0 if it has crashed.
 * \param host A SIMIX host
 * \return 1 if the host is available, 0 otherwise
 */
int SIMIX_req_host_get_state(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_STATE;
  req.host_get_state.host = host;
  SIMIX_request_push(&req);
  return req.host_get_state.result;
}

/**
 * \brief Returns the user data associated to a host.
 *
 * \param host SIMIX host
 * \return the user data of this host
 */
void* SIMIX_req_host_get_data(smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_HOST_GET_DATA;
  req.host_get_data.host = host;
  SIMIX_request_push(&req);
  return req.host_get_data.result;
}

/**
 * \brief Sets the user data associated to a host.
 *
 * The host must not have previous user data associated to it.
 * \param A host SIMIX host
 * \param data The user data to set
 */
void SIMIX_req_host_set_data(smx_host_t host, void *data)
{
  s_smx_req_t req;

  req.call = REQ_HOST_SET_DATA;
  req.host_set_data.host = host;
  req.host_set_data.data = data;
  SIMIX_request_push(&req);
}

/** \brief Creates an action that executes some computation of an host.
 *
 * This function creates a SURF action and allocates the data necessary
 * to create the SIMIX action. It can raise a host_error exception if the host crashed.
 *
 * \param name Name of the execution action to create
 * \param host SIMIX host where the action will be executed
 * \param amount Computation amount (in bytes)
 * \return A new SIMIX execution action
 */
smx_action_t SIMIX_req_host_execute(const char *name, smx_host_t host,
                                double computation_amount)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTE;
  req.host_execute.name = name;
  req.host_execute.host = host;
  req.host_execute.computation_amount = computation_amount;
  SIMIX_request_push(&req);
  return req.host_execute.result;
}

/** \brief Creates an action that may involve parallel computation on
 * several hosts and communication between them.
 *
 * \param name Name of the execution action to create
 * \param host_nb Number of hosts where the action will be executed
 * \param host_list Array (of size host_nb) of hosts where the action will be executed
 * \param computation_amount Array (of size host_nb) of computation amount of hosts (in bytes)
 * \param communication_amount Array (of size host_nb * host_nb) representing the communication
 * amount between each pair of hosts
 * \param amount the SURF action amount
 * \param rate the SURF action rate
 * \return A new SIMIX execution action
 */
smx_action_t SIMIX_req_host_parallel_execute(const char *name,
                                         int host_nb,
                                         smx_host_t *host_list,
                                         double *computation_amount,
                                         double *communication_amount,
                                         double amount,
                                         double rate)
{
  s_smx_req_t req;

  req.call = REQ_HOST_PARALLEL_EXECUTE;
  req.host_parallel_execute.name = name;
  req.host_parallel_execute.host_nb = host_nb;
  req.host_parallel_execute.host_list = host_list;
  req.host_parallel_execute.computation_amount = computation_amount;
  req.host_parallel_execute.communication_amount = communication_amount;
  req.host_parallel_execute.amount = amount;
  req.host_parallel_execute.rate = rate;
  SIMIX_request_push(&req);
  return req.host_parallel_execute.result;
}

/**
 * \brief Destroys an execution action.
 *
 * Destroys an action, freing its memory. This function cannot be called if there are a conditional waiting for it.
 * \param action The execution action to destroy
 */
void SIMIX_req_host_execution_destroy(smx_action_t execution)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_DESTROY;
  req.host_execution_destroy.execution = execution;
  SIMIX_request_push(&req);
}

/**
 * \brief Cancels an execution action.
 *
 * This functions stops the execution. It calls a surf function.
 * \param action The execution action to cancel
 */
void SIMIX_req_host_execution_cancel(smx_action_t execution)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_CANCEL;
  req.host_execution_cancel.execution = execution;
  SIMIX_request_push(&req);
}

/**
 * \brief Returns how much of an execution action remains to be done.
 *
 * \param Action The execution action
 * \return The remaining amount
 */
double SIMIX_req_host_execution_get_remains(smx_action_t execution)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_GET_REMAINS;
  req.host_execution_get_remains.execution = execution;
  SIMIX_request_push(&req);
  return req.host_execution_get_remains.result;
}

/**
 * \brief Returns the state of an execution action.
 *
 * \param execution The execution action
 * \return The state
 */
e_smx_state_t SIMIX_req_host_execution_get_state(smx_action_t execution)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_GET_STATE;
  req.host_execution_get_state.execution = execution;
  SIMIX_request_push(&req);
  return req.host_execution_get_state.result;
}

/**
 * \brief Changes the priority of an execution action.
 *
 * This functions changes the priority only. It calls a surf function.
 * \param execution The execution action
 * \param priority The new priority
 */
void SIMIX_req_host_execution_set_priority(smx_action_t execution, double priority)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_SET_PRIORITY;
  req.host_execution_set_priority.execution = execution;
  req.host_execution_set_priority.priority = priority;
  SIMIX_request_push(&req);
}

/**
 * \brief Waits for the completion of an execution action.
 *
 * \param execution The execution action
 */
void SIMIX_req_host_execution_wait(smx_action_t execution)
{
  s_smx_req_t req;

  req.call = REQ_HOST_EXECUTION_WAIT;
  req.host_execution_wait.execution = execution;
  SIMIX_request_push(&req);
}

/**
 * \brief Creates and runs a new SIMIX process.
 *
 * The structure and the corresponding threada are created and put in the list of ready processes.
 *
 * \param name a name for the process. It is for user-level information and can be NULL.
 * \param code the main function of the process
 * \param data a pointer to any data one may want to attach to the new object. It is for user-level information and can be NULL.
 * It can be retrieved with the function \ref SIMIX_req_process_get_data.
 * \param hostname name of the host where the new agent is executed.
 * \param argc first argument passed to \a code
 * \param argv second argument passed to \a code
 * \param properties the properties of the process
 * \return The new process
 */
smx_process_t SIMIX_req_process_create(const char *name,
                                   xbt_main_func_t code,
                                   void *data,
                                   const char *hostname,
                                   int argc, char **argv,
                                   xbt_dict_t properties)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_CREATE;
  req.process_create.name = name;
  req.process_create.code = code;
  req.process_create.data = data;
  req.process_create.hostname = hostname;
  req.process_create.argc = argc;
  req.process_create.argv = argv;
  req.process_create.properties = properties;
  SIMIX_request_push(&req);
  return req.process_create.result;
}

/** \brief Kills a SIMIX process.
 *
 * This function simply kills a  process.
 *
 * \param process poor victim
 */
void SIMIX_req_process_kill(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_KILL;
  req.process_kill.process = process;
  SIMIX_request_push(&req);
}

/**
 * \brief Migrates an agent to another location.
 *
 * This function changes the value of the host on which \a process is running.
 *
 * \param process the process to migrate
 * \param source name of the previous host
 * \param dest name of the new host
 */
void SIMIX_req_process_change_host(smx_process_t process, const char *source, const char *dest)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_CHANGE_HOST;
  req.process_change_host.process = process;
  req.process_change_host.source = source;
  req.process_change_host.dest = dest;
  SIMIX_request_push(&req);
}

/**
 * \brief Suspends a process.
 *
 * This function suspends the process by suspending the action
 * it was waiting for completion.
 *
 * \param process a SIMIX process
 */
void SIMIX_req_process_suspend(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_SUSPEND;
  req.process_suspend.process = process;
  SIMIX_request_push(&req);
}

/**
 * \brief Resumes a suspended process.
 *
 * This function resumes a suspended process by resuming the action
 * it was waiting for completion.
 *
 * \param process a SIMIX process
 */
void SIMIX_req_process_resume(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_RESUME;
  req.process_resume.process = process;
  SIMIX_request_push(&req);
}

/**
 * \brief Returns the amount of SIMIX processes in the system
 *
 * Maestro internal process is not counted, only user code processes are
 */
int SIMIX_req_process_count(void)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_COUNT;
  SIMIX_request_push(&req);
  return req.process_count.result;
}

/**
 * \brief Return the user data of a #smx_process_t.
 *
 * This functions checks whether \a process is a valid pointer or not and return the user data associated to \a process if it is possible.
 * \param process SIMIX process
 * \return A void pointer to the user data
 */
void* SIMIX_req_process_get_data(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_GET_DATA;
  req.process_get_data.process = process;
  SIMIX_request_push(&req);
  return req.process_get_data.result;
}

/**
 * \brief Set the user data of a #m_process_t.
 *
 * This functions checks whether \a process is a valid pointer or not and set the user data associated to \a process if it is possible.
 * \param process SIMIX process
 * \param data User data
 */
void SIMIX_req_process_set_data(smx_process_t process, void *data)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_SET_DATA;
  req.process_set_data.process = process;
  req.process_set_data.data = data;
  SIMIX_request_push(&req);
}

/**
 * \brief Return the location on which an agent is running.
 *
 * This functions checks whether \a process is a valid pointer or not and return the m_host_t corresponding to the location on which \a process is running.
 * \param process SIMIX process
 * \return SIMIX host
 */
smx_host_t SIMIX_req_process_get_host(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_GET_HOST;
  req.process_get_host.process = process;
  SIMIX_request_push(&req);
  return req.process_get_host.result;
}

/**
 * \brief Return the name of an agent.
 *
 * This functions checks whether \a process is a valid pointer or not and return its name.
 * \param process SIMIX process
 * \return The process name
 */
const char* SIMIX_req_process_get_name(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_GET_NAME;
  req.process_get_name.process = process;
  SIMIX_request_push(&req);
  return req.process_get_name.result;
}

/**
 * \brief Returns true if the process is suspended .
 *
 * This checks whether a process is suspended or not by inspecting the task on which it was waiting for the completion.
 * \param process SIMIX process
 * \return 1, if the process is suspended, else 0.
 */
int SIMIX_req_process_is_suspended(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_IS_SUSPENDED;
  req.process_is_suspended.process = process;
  SIMIX_request_push(&req);
  return req.process_is_suspended.result;
}

/** \ingroup m_process_management
 * \brief Return the properties
 *
 * This functions returns the properties associated with this process
 */
xbt_dict_t SIMIX_req_process_get_properties(smx_process_t process)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_GET_PROPERTIES;
  req.process_get_properties.process = process;
  SIMIX_request_push(&req);
  return req.process_get_properties.result;
}

/** \brief Creates a new sleep SIMIX action.
 *
 * This function creates a SURF action and allocates the data necessary
 * to create the SIMIX action. It can raise a host_error exception if the
 * host crashed. The default SIMIX name of the action is "sleep".
 *
 * 	\param duration Time duration of the sleep.
 * 	\return A result telling whether the sleep was successful
 */
e_smx_state_t SIMIX_req_process_sleep(double duration)
{
  s_smx_req_t req;

  req.call = REQ_PROCESS_SLEEP;
  req.process_sleep.duration = duration;
  SIMIX_request_push(&req);
  return req.process_sleep.result;
}

/**
 *  \brief Creates a new rendez-vous point
 *  \param name The name of the rendez-vous point
 *  \return The created rendez-vous point
 */
smx_rdv_t SIMIX_req_rdv_create(const char *name)
{
  s_smx_req_t req;

  req.call = REQ_RDV_CREATE;
  req.rdv_create.name = name;

  SIMIX_request_push(&req);
  return req.rdv_create.result;
}


/**
 *  \brief Destroy a rendez-vous point
 *  \param name The rendez-vous point to destroy
 */
void SIMIX_req_rdv_destroy(smx_rdv_t rdv)
{
  s_smx_req_t req;

  req.call = REQ_RDV_DESTROY; 
  req.rdv_destroy.rdv = rdv;

  SIMIX_request_push(&req);
}

smx_rdv_t SIMIX_req_rdv_get_by_name(const char *name)
{
  s_smx_req_t req;

  req.call = REQ_RDV_GEY_BY_NAME;
  req.rdv_get_by_name.name = name;
  SIMIX_request_push(&req);
  return req.rdv_get_by_name.result;
}

/**
 *  \brief counts the number of communication requests of a given host pending
 *         on a rendez-vous point
 *  \param rdv The rendez-vous point
 *  \param host The host to be counted
 *  \return The number of comm request pending in the rdv
 */
int SIMIX_req_rdv_comm_count_by_host(smx_rdv_t rdv, smx_host_t host)
{
  s_smx_req_t req;

  req.call = REQ_RDV_COMM_COUNT_BY_HOST; 
  req.rdv_comm_count_by_host.rdv = rdv;
  req.rdv_comm_count_by_host.host = host;

  SIMIX_request_push(&req);
  return req.rdv_comm_count_by_host.result;
}

/**
 *  \brief returns the communication at the head of the rendez-vous
 *  \param rdv The rendez-vous point
 *  \return The communication or NULL if empty
 */
smx_action_t SIMIX_req_rdv_get_head(smx_rdv_t rdv)
{
  s_smx_req_t req;

  req.call = REQ_RDV_GET_HEAD; 
  req.rdv_get_head.rdv = rdv;

  SIMIX_request_push(&req);
  return req.rdv_get_head.result;
}

smx_action_t SIMIX_req_comm_isend(smx_rdv_t rdv, double task_size, double rate,
                              void *src_buff, size_t src_buff_size, void *data)
{
  s_smx_req_t req;

  xbt_assert0(rdv, "No rendez-vous point defined for isend");

  req.call = REQ_COMM_ISEND;
  req.comm_isend.rdv = rdv;
  req.comm_isend.task_size = task_size;
  req.comm_isend.rate = rate;
  req.comm_isend.src_buff = src_buff;
  req.comm_isend.src_buff_size = src_buff_size;
  req.comm_isend.data = data;

  SIMIX_request_push(&req);
  return req.comm_isend.result;
}

smx_action_t SIMIX_req_comm_irecv(smx_rdv_t rdv, void *dst_buff, size_t * dst_buff_size)
{
  s_smx_req_t req;

  xbt_assert0(rdv, "No rendez-vous point defined for isend");

  req.call = REQ_COMM_IRECV;
  req.comm_irecv.rdv = rdv;
  req.comm_irecv.dst_buff = dst_buff;
  req.comm_irecv.dst_buff_size = dst_buff_size;

  SIMIX_request_push(&req);
  return req.comm_irecv.result;
}

void SIMIX_req_comm_destroy(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_DESTROY;
  req.comm_destroy.comm = comm;

  SIMIX_request_push(&req);
}

void SIMIX_req_comm_cancel(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_CANCEL;
  req.comm_cancel.comm = comm;

  SIMIX_request_push(&req);
}

unsigned int SIMIX_req_comm_waitany(xbt_dynar_t comms)
{
  s_smx_req_t req;

  req.call = REQ_COMM_WAITANY;
  req.comm_waitany.comms = comms;

  SIMIX_request_push(&req);
  return req.comm_waitany.result;
}

void SIMIX_req_comm_wait(smx_action_t comm, double timeout)
{
  s_smx_req_t req;

  req.call = REQ_COMM_WAIT;
  req.comm_wait.comm = comm;
  req.comm_wait.timeout = timeout;

  SIMIX_request_push(&req);
}

int SIMIX_req_comm_test(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_TEST;
  req.comm_test.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_test.result;
}

double SIMIX_req_comm_get_remains(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_REMAINS;
  req.comm_get_remains.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_remains.result;
}

e_smx_state_t SIMIX_req_comm_get_state(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_STATE;
  req.comm_get_state.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_state.result;
}

void *SIMIX_req_comm_get_data(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_DATA;
  req.comm_get_data.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_data.result;
}

void *SIMIX_req_comm_get_src_buff(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_SRC_BUFF;
  req.comm_get_src_buff.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_src_buff.result;
}

void *SIMIX_req_comm_get_dst_buff(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_DST_BUFF;
  req.comm_get_dst_buff.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_dst_buff.result;
}

size_t SIMIX_req_comm_get_src_buff_size(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_SRC_BUFF_SIZE;
  req.comm_get_src_buff_size.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_src_buff_size.result;
}

size_t SIMIX_req_comm_get_dst_buff_size(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_DST_BUFF_SIZE;
  req.comm_get_dst_buff_size.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_dst_buff_size.result;
}

smx_process_t SIMIX_req_comm_get_src_proc(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_SRC_PROC;
  req.comm_get_src_proc.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_src_proc.result;
}

smx_process_t SIMIX_req_comm_get_dst_proc(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_GET_DST_PROC;
  req.comm_get_dst_proc.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_get_dst_proc.result;
}

#ifdef HAVE_LATENCY_BOUND_TRACKING
int SIMIX_req_comm_is_latency_bounded(smx_action_t comm)
{
  s_smx_req_t req;

  req.call = REQ_COMM_IS_LATENCY_BOUNDED;
  req.comm_is_latency_bounded.comm = comm;

  SIMIX_request_push(&req);
  return req.comm_is_latency_bounded.result;
}
#endif

smx_mutex_t SIMIX_req_mutex_init(void)
{
  s_smx_req_t req;

  req.call = REQ_MUTEX_INIT;

  SIMIX_request_push(&req);
  return req.mutex_init.result;
}

void SIMIX_req_mutex_destroy(smx_mutex_t mutex)
{
  s_smx_req_t req;

  req.call = REQ_MUTEX_DESTROY;
  req.mutex_destroy.mutex = mutex;

  SIMIX_request_push(&req);
}

void SIMIX_req_mutex_lock(smx_mutex_t mutex)
{
  s_smx_req_t req;

  req.call = REQ_MUTEX_LOCK;
  req.mutex_lock.mutex = mutex;

  SIMIX_request_push(&req);
}

int SIMIX_req_mutex_trylock(smx_mutex_t mutex)
{
  s_smx_req_t req;

  req.call = REQ_MUTEX_TRYLOCK;
  req.mutex_trylock.mutex = mutex;

  SIMIX_request_push(&req);
  return req.mutex_trylock.result;
}

void SIMIX_req_mutex_unlock(smx_mutex_t mutex)
{
  s_smx_req_t req;

  req.call = REQ_MUTEX_UNLOCK;
  req.mutex_unlock.mutex = mutex;

  SIMIX_request_push(&req);
}


smx_cond_t SIMIX_req_cond_init(void)
{
  s_smx_req_t req;

  req.call = REQ_COND_INIT;

  SIMIX_request_push(&req);
  return req.cond_init.result;
}

void SIMIX_req_cond_destroy(smx_cond_t cond)
{
  s_smx_req_t req;

  req.call = REQ_COND_DESTROY;
  req.cond_destroy.cond = cond;

  SIMIX_request_push(&req);
}

void SIMIX_req_cond_signal(smx_cond_t cond)
{
  s_smx_req_t req;

  req.call = REQ_COND_SIGNAL;
  req.cond_signal.cond = cond;

  SIMIX_request_push(&req);
}

void SIMIX_req_cond_wait(smx_cond_t cond, smx_mutex_t mutex)
{
  s_smx_req_t req;

  req.call = REQ_COND_WAIT;
  req.cond_wait.cond = cond;
  req.cond_wait.mutex = mutex;

  SIMIX_request_push(&req);
}

void SIMIX_req_cond_wait_timeout(smx_cond_t cond,
                                 smx_mutex_t mutex,
                                 double timeout)
{
  s_smx_req_t req;

  req.call = REQ_COND_WAIT_TIMEOUT;
  req.cond_wait_timeout.cond = cond;
  req.cond_wait_timeout.mutex = mutex;
  req.cond_wait_timeout.timeout = timeout;

  SIMIX_request_push(&req);
}

void SIMIX_req_cond_broadcast(smx_cond_t cond)
{
  s_smx_req_t req;

  req.call = REQ_COND_BROADCAST;
  req.cond_broadcast.cond = cond;

  SIMIX_request_push(&req);
}


smx_sem_t SIMIX_req_sem_init(int capacity)
{
  s_smx_req_t req;

  req.call = REQ_SEM_INIT;
  req.sem_init.capacity = capacity;

  SIMIX_request_push(&req);
  return req.sem_init.result;
}

void SIMIX_req_sem_destroy(smx_sem_t sem)
{
  s_smx_req_t req;

  req.call = REQ_SEM_DESTROY;
  req.sem_destroy.sem = sem;

  SIMIX_request_push(&req);
}

void SIMIX_req_sem_release(smx_sem_t sem)
{
  s_smx_req_t req;

  req.call = REQ_SEM_RELEASE;
  req.sem_release.sem = sem;

  SIMIX_request_push(&req);
}

int SIMIX_req_sem_would_block(smx_sem_t sem)
{
  s_smx_req_t req;

  req.call = REQ_SEM_WOULD_BLOCK;
  req.sem_would_block.sem = sem;

  SIMIX_request_push(&req);
  return req.sem_would_block.result;
}

void SIMIX_req_sem_acquire(smx_sem_t sem)
{
  s_smx_req_t req;

  req.call = REQ_SEM_ACQUIRE;
  req.sem_acquire.sem = sem;

  SIMIX_request_push(&req);
}

void SIMIX_req_sem_acquire_timeout(smx_sem_t sem, double timeout)
{
  s_smx_req_t req;

  req.call = REQ_SEM_ACQUIRE_TIMEOUT;
  req.sem_acquire_timeout.sem = sem;
  req.sem_acquire_timeout.timeout = timeout;

  SIMIX_request_push(&req);
}

int SIMIX_req_sem_get_capacity(smx_sem_t sem)
{
  s_smx_req_t req;

  req.call = REQ_SEM_GET_CAPACITY;
  req.sem_get_capacity.sem = sem;

  SIMIX_request_push(&req);
  return req.sem_get_capacity.result;
}


