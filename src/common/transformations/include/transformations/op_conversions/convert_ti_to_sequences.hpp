// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <memory>
#include <vector>

#include "openvino/pass/graph_rewrite.hpp"
#include "transformations_visibility.hpp"

namespace ov {
namespace pass {

class TRANSFORMATIONS_API ConvertTensorIteratorToLSTMSequence;
class TRANSFORMATIONS_API ConvertTensorIteratorToRNNSequence;
class TRANSFORMATIONS_API ConvertTensorIteratorToGRUSequence;
class TRANSFORMATIONS_API ConvertTensorIteratorToSequence;

class TRANSFORMATIONS_API ConvertLoopWithSlicedInputConcatOutputToLSTMSequence;
class TRANSFORMATIONS_API ConvertLoopWithScatterUpdateToLSTMSequence;
class TRANSFORMATIONS_API ConvertLoopToLSTMSequence;
class TRANSFORMATIONS_API FuseReverseLSTMSequence;

class TRANSFORMATIONS_API FuseLSTMSequencesToBidirectionalLSTMSequence;

}  // namespace pass
}  // namespace ov

/**
 * @ingroup ov_transformation_common_api
 * @brief Finds all TensorIterator layers, detects the pattern Squeeze->LSTMCell->Unsqueeze in the TensorIterator body,
 * converts this pattern to LSTMSequence layer and replaces them TensorIterator.
 */

class ov::pass::ConvertTensorIteratorToLSTMSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("ConvertTensorIteratorToLSTMSequence");
    ConvertTensorIteratorToLSTMSequence();
};

/**
 * @ingroup ov_transformation_common_api
 * @brief Finds all TensorIterator layers, detects the pattern Squeeze->RNNCell->Unsqueeze in the TensorIterator body,
 * converts this pattern to RNNSequence layer and replaces them TensorIterator.
 */

class ov::pass::ConvertTensorIteratorToRNNSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("ConvertTensorIteratorToRNNSequence");
    ConvertTensorIteratorToRNNSequence();
};

/**
 * @ingroup ov_transformation_common_api
 * @brief Finds all TensorIterator layers, detects the pattern Squeeze->GRUCell->Unsqueeze in the TensorIterator body,
 * converts this pattern to GRUSequence layer and replaces them TensorIterator.
 */

class ov::pass::ConvertTensorIteratorToGRUSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("ConvertTensorIteratorToGRUSequence");
    ConvertTensorIteratorToGRUSequence();
};

class ov::pass::ConvertTensorIteratorToSequence : public GraphRewrite {
public:
    OPENVINO_GRAPH_REWRITE_RTTI("ConvertTensorIteratorToSequence");
    ConvertTensorIteratorToSequence();
};

class ov::pass::ConvertLoopWithSlicedInputConcatOutputToLSTMSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("ConvertLoopWithSlicedInputConcatOutputToLSTMSequence");
    ConvertLoopWithSlicedInputConcatOutputToLSTMSequence();
};

class ov::pass::ConvertLoopWithScatterUpdateToLSTMSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("ConvertLoopWithScatterUpdateToLSTMSequence");
    ConvertLoopWithScatterUpdateToLSTMSequence();
};

/**
 * @ingroup ov_transformation_common_api
 * @brief Replaces Loop with LSTMCell inside to LSTMSequence
 */
class ov::pass::ConvertLoopToLSTMSequence : public ov::pass::GraphRewrite {
public:
    OPENVINO_GRAPH_REWRITE_RTTI("ConvertLoopToLSTMSequence");
    ConvertLoopToLSTMSequence() {
        add_matcher<ov::pass::ConvertLoopWithScatterUpdateToLSTMSequence>();
        add_matcher<ov::pass::ConvertLoopWithSlicedInputConcatOutputToLSTMSequence>();
    }
};

/**
 * @ingroup ov_transformation_common_api
 * @brief Fuses ReverseSequence->LSTM->ReverseSequence to LSTMSequence with REVERSE direction flag
 */
class ov::pass::FuseReverseLSTMSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("FuseReverseLSTMSequence");
    FuseReverseLSTMSequence();
};

/**
 * @ingroup ov_transformation_common_api
 * @brief Replaces two LSTMSequences to one bidirectional LSTMSequence
 */
class ov::pass::FuseLSTMSequencesToBidirectionalLSTMSequence : public ov::pass::MatcherPass {
public:
    OPENVINO_MATCHER_PASS_RTTI("FuseLSTMSequencesToBidirectionalLSTMSequence");
    FuseLSTMSequencesToBidirectionalLSTMSequence();
};
