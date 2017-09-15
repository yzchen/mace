//
// Copyright (c) 2017 XiaoMi All rights reserved.
//

#include "mace/core/operator.h"
#include "mace/ops/ops_test_util.h"

namespace mace {

class ReluOpTest : public OpsTestBase {};

TEST_F(ReluOpTest, ReluOp) {
  // Construct graph
  auto& net = test_net();
  OpDefBuilder("Relu", "ReluTest")
      .Input("Input")
      .Output("Output")
      .Finalize(net.operator_def());

  // Add input data
  net.AddRandomInput<float>("Input", {1, 2, 3, 4});

  // Run
  net.RunOp();

  Tensor expected;
  expected.Copy(*net.GetOutput("Output"));

  // Check
  net.RunOp(DeviceType::NEON);

  ExpectTensorNear<float>(expected, *net.GetOutput("Output"), 0.01);
}

}  // namespace mace
