/**
 *  This file is a part of blacspp (see LICENSE)
 *
 *  Copyright (c) 2019-2020 David Williams-Young
 *  All rights reserved
 */
#pragma once
#include <blacspp/grid.hpp>
#include <blacspp/wrappers/broadcast.hpp>
#include <blacspp/util/type_conversions.hpp>



// XXX: DOCUMENTATION INCORRECT!!!!!!!!!!!!!!!!!!!!!!
namespace blacspp {


/**
 *  \brief General 2D broadcast send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  @tparam T Type of buffer to send. Must be BLACS enabled.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Pointer of buffer to send
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T>
  gebs2d( const Grid& grid, const Scope scope, const Topology top,
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA ) {

  auto SCOPE = detail::type_string( scope );
  auto TOP   = detail::type_string( top   );
  wrappers::gebs2d( grid.context(), SCOPE.c_str(), TOP.c_str(), M, N, A, LDA );

}


/**
 *  \brief General point-to-point 2D send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  Sends a buffer which is managed by a C++ container.
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *
 */
template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
  gebs2d( const Grid& grid, const Scope scope, const Topology top,
          const blacs_int M, const blacs_int N, const Container& A, 
          const blacs_int LDA ) {

  gebs2d( grid, scope, top, M, N, A.data(), LDA );

}

/**
 *  \brief General point-to-point 2D send.
 *
 *  Performs a general (rectangular) point-to-point 2D send on a BLACS grid.
 *  Sends a 2D buffer (col-major) to a specified process coordinate on the BLACS
 *  grid.
 *
 *  Sends a buffer which is managed by a C++ container. Size of buffer deduced 
 *  from Container::size().
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function and
 *                    Container::size() -> std::size_t member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *
 */
template <class Container>
std::enable_if_t< detail::has_size_member_v<Container> >
  gebs2d( const Grid& grid, const Scope scope, const Topology top,
          const Container& A ) {

  gebs2d( grid, scope, top, A.size(), 1, A, A.size() );

}



/**
 *  \brief Triangular point-to-point 2D send.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D send on a BLACS grid.
 *  Sends the specified triangular portion of a  2D buffer (col-major) to a specified 
 *  process coordinate on the BLACS grid.
 *
 *  @tparam T Type of buffer to send. Must be BLACS enabled.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] UPLO  (local) Which triangle of the buffer to send (upper/lower)
 *  @param[in] DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Pointer of buffer to send
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbs2d( const Grid& grid, const Scope scope, const Topology top,
          const Triangle uplo, const Diagonal diag,
          const blacs_int M, const blacs_int N, const T* A, const blacs_int LDA ) {

  auto SCOPE = detail::type_string( scope );
  auto TOP   = detail::type_string( top   );
  auto UPLO  = detail::type_string( uplo  );
  auto DIAG  = detail::type_string( diag  );

  wrappers::trbs2d( grid.context(), SCOPE.c_str(), TOP.c_str(), UPLO.c_str(), DIAG.c_str(), M, N, A, LDA );

}

/**
 *  \brief Triangular point-to-point 2D send.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D send on a BLACS grid.
 *  Sends the specified triangular portion of a  2D buffer (col-major) to a specified 
 *  process coordinate on the BLACS grid.
 *
 *  Sends a buffer which is managed by a C++ container.
 *
 *  @tparam Container Type of container which manages the memory of the buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in] grid  (local) BLACS grid which defined the communication context.
 *  @param[in] UPLO  (local) Which triangle of the buffer to send (upper/lower)
 *  @param[in] DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in] M     (local) Number of rows of the buffer to send
 *  @param[in] N     (local) Number of columns of the buffer to send
 *  @param[in] A     (local) Buffer to send (managed by some container)
 *  @param[in] LDA   (local) Leading dimension of the buffer to send
 *
 */
template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
  trbs2d( const Grid& grid, const Scope scope, const Topology top,
          const Triangle uplo, const Diagonal diag,
          const blacs_int M, const blacs_int N, const Container& A, 
          const blacs_int LDA ) {

  trbs2d( grid, scope, top, uplo, diag, M, N, A.data(), LDA );

}














  
/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  @tparam T Type of buffer to recieve. Must be BLACS enabled.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Pointer of buffer to store recieved data
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  gebr2d( const Grid& grid, const Scope scope, const Topology top,
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA ) {

  auto SCOPE = detail::type_string( scope );
  auto TOP   = detail::type_string( top   );
  wrappers::gebr2d( grid.context(), SCOPE.c_str(), TOP.c_str(), M, N, A, LDA );

}

/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  Recieve buffer managed by C++ container
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *
 */
template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
  gebr2d( const Grid& grid, const Scope scope, const Topology top,
          const blacs_int M, const blacs_int N, Container& A, const blacs_int LDA ) {

  gebr2d( grid, scope, top, M, N, A.data(), LDA );

}

/**
 *  \brief General point-to-point 2D recieve.
 *
 *  Performs a general (rectangular) point-to-point 2D recieve on a BLACS grid.
 *  Recieves a 2D buffer (col-major) from a specified source process coordinate on the BLACS
 *  grid.
 *
 *  Recieve buffer managed by C++ container. Size of buffer deduced from Container::size()
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function and
 *                    Container::size() -> std::size_t member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *
 */
template <class Container>
std::enable_if_t< detail::has_size_member_v<Container> >
  gebr2d( const Grid& grid, const Scope scope, const Topology top, Container& A ) { 

  gebr2d( grid, scope, top, A.size(), 1, A, A.size() );

}


/**
 *  \brief Triangular point-to-point 2D recieve.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D recieve on a BLACS grid.
 *  Recieves the specified triangular portin of a 2D buffer (col-major) from a 
 *  specified source process coordinate on the BLACS grid.
 *
 *  @tparam T Type of buffer to recieve. Must be BLACS enabled.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     UPLO  (local) Which triangle of the buffer to recieve (upper/lower)
 *  @param[in]     DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Pointer of buffer to store recieved data
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *
 */
template <typename T>
detail::enable_if_blacs_supported_t<T> 
  trbr2d( const Grid& grid, const Scope scope, const Topology top,
          const Triangle uplo, const Diagonal diag,
          const blacs_int M, const blacs_int N, T* A, const blacs_int LDA ) { 

  auto SCOPE = detail::type_string( scope );
  auto TOP   = detail::type_string( top   );
  auto UPLO  = detail::type_string( uplo  );
  auto DIAG  = detail::type_string( diag  );

  wrappers::trbr2d( grid.context(), SCOPE.c_str(), TOP.c_str(), UPLO.c_str(), DIAG.c_str(), M, N, A, LDA );

}

/**
 *  \brief Triangular point-to-point 2D recieve.
 *
 *  Performs a triangular (upper/lower) point-to-point 2D recieve on a BLACS grid.
 *  Recieves the specified triangular portin of a 2D buffer (col-major) from a 
 *  specified source process coordinate on the BLACS grid.
 *
 *  Recieve buffer managed by C++ container
 *
 *  @tparam Container Type of container which manages the memory of the revieve buffer.
 *                    Must have Container::data() -> pointer member function.
 *
 *  @param[in]     grid  (local) BLACS grid which defined the communication context.
 *  @param[in]     UPLO  (local) Which triangle of the buffer to recieve (upper/lower)
 *  @param[in]     DIAG  (local) Whether to imply that the diagonal of the buffer is unit.
 *  @param[in]     M     (local) Number of rows of the buffer to recieve
 *  @param[in]     N     (local) Number of columns of the buffer to recieve
 *  @param[in/out] A     (local) Recieve buffer (managed by some container)
 *  @param[in]     LDA   (local) Leading dimension of the buffer to store recieved data.
 *
 */
template <class Container>
std::enable_if_t< detail::has_data_member_v<Container> >
  trbr2d( const Grid& grid, const Scope scope, const Topology top,
          const Triangle uplo, const Diagonal diag,
          const blacs_int M, const blacs_int N, Container& A, const blacs_int LDA ) {

  trbr2d( grid, scope, top, uplo, diag, M, N, A.data(), LDA );

}


}
