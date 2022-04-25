#pragma once

#include <torch/csrc/lazy/core/ir.h>
#include <torch/csrc/lazy/core/ir_builder.h>
#include <torch/csrc/lazy/core/internal_ops/ltc_ops.h>
#include <torch/csrc/lazy/core/shape_inference.h>


#include "mlir_node.h"
#include "dynamic_ir.h"
#include "view_ops/narrow.h"
#include "view_ops/select_view_update.h"
#include "view_ops/as_strided_view_update.h"
#include "view_ops/permute.h"
#include "view_ops/diagonal_view_update.h"
#include "view_ops/resize.h"
#include "view_ops/squeeze.h"
#include "view_ops/diagonal.h"
#include "view_ops/narrow_view_update.h"
#include "view_ops/as_strided.h"
#include "view_ops/unsqueeze.h"
#include "view_ops/select.h"
#include "view_ops/view.h"
#include "ops/cast.h"
#include "ops/arithmetic_ir_ops.h"
#include "ops/device_data.h"
#include "ops/generic.h"
#include "ops/batch_norm_ops.h"
#include "ops/to_copy.h"
#include "ops/scalar.h"
#include "ops/random_ops.h"
#include "ops/expand.h"

// This file contains the TorchScript IrBuilder

namespace torch {
namespace lazy {


struct TorchMlirIrBuilder: IrBuilder {
  NodePtr MakeDeviceData(const std::shared_ptr<BackendData>& data) const override { return MakeNode<DeviceData>(data); }
  NodePtr MakeScalar(const at::Scalar& value, const at::ScalarType& type) const override { return MakeNode<Scalar>(value, type); }
  NodePtr MakeExpand(const Value& input0, const std::vector<int64_t>& size, const bool& is_scalar_expand) const override { return MakeNode<Expand>(input0, size, is_scalar_expand); }
  NodePtr MakeView(const Value& input0, const std::vector<int64_t>& output_size) const override { return MakeNode<View>(input0, output_size); }
  NodePtr MakeCast(const Value& input0, const at::ScalarType& dtype, const c10::optional<at::ScalarType>& stype = c10::nullopt) const override { return MakeNode<Cast>(input0, dtype, stype); }
  NodePtr MakeTensorList(const OpList& inputs) const override { return MakeNode<TensorList>(inputs); }
  NodePtr MakeAsStridedViewUpdate(const Value& input0, const Value& input1, const std::vector<int64_t>& size, const std::vector<int64_t>& stride, const int64_t& storage_offset) const override { return MakeNode<AsStridedViewUpdate>(input0, input1, size, stride, storage_offset); }
  NodePtr MakeAsStrided(const Value& input0, const std::vector<int64_t>& size, const std::vector<int64_t>& stride, const int64_t& storage_offset) const override { return MakeNode<AsStrided>(input0, size, stride, storage_offset); }
  NodePtr MakeDiagonalViewUpdate(const Value& input0, const Value& input1, const int64_t& offset, const int64_t& dim1, const int64_t& dim2) const override { return MakeNode<DiagonalViewUpdate>(input0, input1, offset, dim1, dim2); }
  NodePtr MakeDiagonal(const Value& input0, const int64_t& offset, const int64_t& dim1, const int64_t& dim2) const override { return MakeNode<Diagonal>(input0, offset, dim1, dim2); }
  NodePtr MakeNarrowViewUpdate(const Value& input0, const Value& input1, const std::vector<int64_t>& base_indices) const override { return MakeNode<NarrowViewUpdate>(input0, input1, base_indices); }
  NodePtr MakeNarrow(const Value& input0, const std::vector<int64_t>& base_indices, const std::vector<int64_t>& sizes) const override { return MakeNode<Narrow>(input0, base_indices, sizes); }
  NodePtr MakePermute(const Value& input0, const std::vector<int64_t>& dims) const override { return MakeNode<Permute>(input0, dims); }
  NodePtr MakeResize(const Value& input0, const std::vector<int64_t>& size) const override { return MakeNode<Resize>(input0, size); }
  NodePtr MakeSelectViewUpdate(const Value& input0, const Value& input1, const int64_t& dim, const int64_t& start, const int64_t& end, const int64_t& stride) const override { return MakeNode<SelectViewUpdate>(input0, input1, dim, start, end, stride); }
  NodePtr MakeSelect(const Value& input0, const int64_t& dim, const int64_t& start, const int64_t& end, const int64_t& stride) const override { return MakeNode<Select>(input0, dim, start, end, stride); }
  NodePtr MakeSqueeze(const Value& input0, const int& dim) const override { return MakeNode<Squeeze>(input0, dim); }
  NodePtr MakeUnsqueeze(const Value& input0, const int& dim) const override { return MakeNode<Unsqueeze>(input0, dim); }

  // dynamic ir nodes
  NodePtr MakeSizeNode(const Value& input, size_t dim) const override { return MakeNode<SizeNode>(input, dim); }
  NodePtr MakeSizeAdd(const Value& a, const Value& b) const override { return MakeNode<SizeAdd>(a, b); }
  NodePtr MakeSizeMul(const Value& a, const Value& b) const override { return MakeNode<SizeMul>(a, b); }
  NodePtr MakeSizeDiv(const Value& a, const Value& b) const override { return MakeNode<SizeDiv>(a, b); }
};

} // namespace lazy
} // namespace torch
