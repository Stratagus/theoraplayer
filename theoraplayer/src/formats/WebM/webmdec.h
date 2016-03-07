/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines a WebM coded interface.

#if 0
//#ifndef WEBMDEC_H_
#define WEBMDEC_H_

#include "./tools_common.h"

#include "DataSource.h"

using namespace theoraplayer; // TODOth - remove later


	struct VpxInputContext;

	struct WebmInputContext {
		void *reader;
		void *segment;
		uint8_t *buffer;
		const void *cluster;
		const void *block_entry;
		const void *block;
		int block_frame_index;
		int video_track_index;
		uint64_t timestamp_ns;
		int is_key_frame;
		int reached_eos;
		float duration;
	};

	// Checks if the input is a WebM file. If so, initializes WebMInputContext so
	// that webm_read_frame can be called to retrieve a video frame.
	// Returns 1 on success and 0 on failure or input is not WebM file.
	// TODO(vigneshv): Refactor this function into two smaller functions specific
	// to their task.
	// TODOth - remove this namespace
	namespace TheoraWebmDec{
		int file_is_webm(DataSource* dataSource, struct WebmInputContext *webm_ctx,
		struct VpxInputContext *vpx_ctx);

		// Reads a WebM Video Frame. Memory for the buffer is created, owned and managed
		// by this function. For the first call, |buffer| should be NULL and
		// |*bytes_in_buffer| should be 0. Once all the frames are read and used,
		// webm_free() should be called, otherwise there will be a leak.
		// Parameters:
		//      webm_ctx - WebmInputContext object
		//      buffer - pointer where the frame data will be filled.
		//      bytes_in_buffer - pointer to buffer size.
		//      buffer_size - unused TODO(vigneshv): remove this
		// Return values:
		//      0 - Success
		//      1 - End of Stream
		//     -1 - Error
		// TODO(vigneshv): Make the return values consistent across all functions in
		// this file.
		int webm_read_frame(struct WebmInputContext *webm_ctx,
			uint8_t **buffer,
			size_t *bytes_in_buffer,
			size_t *buffer_size);

		// Guesses the frame rate of the input file based on the container timestamps.
		int webm_guess_framerate(DataSource* dataSource, struct WebmInputContext *webm_ctx,
		struct VpxInputContext *vpx_ctx);

		int webm_guess_duration(struct WebmInputContext* webm_ctx);

		void webm_rewind(struct WebmInputContext* webm_ctx);

		// Resets the WebMInputContext.
		void webm_free(struct WebmInputContext *webm_ctx);
	}


#endif  // WEBMDEC_H_