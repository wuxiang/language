class EditionController < ApplicationController
  def show
      @work = Edition.find(params[:id]);
  end
end
