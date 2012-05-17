require 'test_helper'

class WorkControllerTest < ActionController::TestCase
  test "should get show" do
    get :show
    assert_response :success
  end

end
